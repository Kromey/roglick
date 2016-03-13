from roglick import logging


logger = logging.getLogger(__name__)


# Constants denoting Event status after a handler has processed it
#  PASS: The Event should be passed along the chain
#  DONE: The Event has been resolved and no further processing should be done
#  FAILED: The handler has canceled/aborted the Event; no further processing
PASS = 0
DONE = 1
FAILED = 2


class Event(object):
    """Base class from which all Events should inherit."""
    def __init__(self, entity_source=None, entity_target=None):
        self.entity_source = entity_source
        self.entity_target = entity_target

    def __repr__(self):
        return "{cls}({esource}, {etarget})".format(
                cls=self.__class__.__name__,
                esource=self.entity_source,
                etarget=self.entity_target)


registry = {}


def register(handler, event_class):
    """Register an event handler for the specified Events.

    The handler is expected to return DONE if it has fully resolved the Event,
    PASS if the Event is not yet fully resolved, or FAILED if the Event is
    canceled.

    The event_class parameter is either an Event subclass, or an iterable object
    of Event subclasses, that the handler should be called for.
    """
    try:
        for event in event_class:
            # Iterate through the event
            register(handler, event)
    except TypeError:
        # events isn't iterable, assume it's just one event
        if event_class not in registry:
            registry[event_class] = []

        registry[event_class].append(handler)


def dispatch(event):
    """Dispatch an Event to the registered handlers.

    The Event will be broken out into its type (class) and sub-types (base
    classes); going up the class hierarchy, for each class all handlers for
    that type will be called in the order they were registered.

    For example, consider a FooEvent class that inherits from BarEvent, which
    in turn inherits from Event. In order:
      1) All handlers for FooEvent will be called in the order they registered
      2) All handlers for BarEvent will be called, in register order
      3) All handlers for Event will be caled, in register order
    This means that more "specific" handlers will always be invoked before more
    general ones, while respecting the order of registration at each "level".
    """
    logger.info("Dispatch event %s", event)
    for etype in event.__class__.__mro__:
        for handler in registry.get(etype, ()):
            result = handler(event)
            if PASS != result:
                logger.debug("Handler %s stopped event with %s",
                        handler.__name__, result)
                return result

    logger.debug("Event passed through all handlers")
    return PASS


def event_handler(*events):
    """Decorator to mark a class method as an event handler.

    When the decorator is applied, you must pass the Event classes the method
    will listen for to the decorator, e.g.
      @event_handler(EventOne, EventTwo)
      def handler_method(self, event):
          pass
    """
    def decorator(meth):
        meth.handled_events = events
        return meth
    return decorator


def register_object(obj):
    """Register all methods decorated with event_handler for their events."""
    for attr in dir(obj):
        try:
            handler = getattr(obj, attr)
            register(handler, handler.handled_events)
        except AttributeError:
            continue

