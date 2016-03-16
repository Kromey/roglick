from roglick import logging


logger = logging.getLogger(__name__)


class Event(object):
    """Base class from which all Events should inherit."""
    def __init__(self, entity_source=None, entity_target=None):
        self.entity_source = entity_source
        self.entity_target = entity_target

        self._propagate = True

    def stop(self):
        """Stop an event from continuing to propagate to other handlers.

        Note that this should only be used when an event is being "cancelled"
        or in situations when it is being replaced by another dispatched event.
        """
        self._propagate = False

    @property
    def propagate(self):
        """Returns True if the event should continue to propagate to handlers.

        This property is True until the stop() method is called on this event.
        """
        return self._propagate

    def __repr__(self):
        return "{cls}({esource}, {etarget})".format(
                cls=self.__class__.__name__,
                esource=self.entity_source,
                etarget=self.entity_target)


registry = {}


def register(handler, event_class=None):
    """Register an event handler for the specified Events.

    The event_class parameter is either an Event subclass, or an iterable object
    of Event subclasses, that the handler should be called for. If the
    event_class parameter is not supplied or is None, this function will first
    try to use the handled_events attribute of the handler or, if that does not
    exist, it will iterate through of handler's attributes and methods trying
    the same thing on each.
    """
    if event_class is None:
        try:
            register(handler, handler.handled_events)
        except AttributeError:
            for attr in dir(handler):
                try:
                    meth = getattr(handler, attr)
                    register(meth, meth.handled_events)
                except AttributeError:
                    continue
    else:
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
    logger.info("%s: Dispatched", event)
    for etype in event.__class__.__mro__:
        for handler in registry.get(etype, ()):
            handler(event)
            if not event.propagate:
                logger.debug("%s: Stopped by handler %s", event, handler.__name__)
                return

    logger.debug("%s: Finished propagating through all handlers", event)


def event_handler(*events):
    """Decorator to mark a class method as an event handler.

    When the decorator is applied, you must pass the Event classes the method
    will listen for to the decorator, e.g.
      @event_handler(EventOne, EventTwo)
      def handler_method(self, event):
          pass
    An instance of this class can then be passed to the register() function,
    which will identify and register the decorated method(s) for the listed
    events.
    """
    def decorator(meth):
        meth.handled_events = events
        return meth
    return decorator

