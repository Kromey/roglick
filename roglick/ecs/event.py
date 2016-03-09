NOTDONE = 0
SUCCESSFUL = 1
FAILED = 2

class Event(object):
    """Base class from which all Events should inherit."""
    def __init__(self, entity_source=None, entity_target=None):
        self.entity_source = entity_source
        self.entity_target = entity_target


registry = {}

def register(handler, event_class):
    """Register an event handler for the specified Events.

    The handler is expected to return DONE if it has fully resolved the Event,
    or NOTDONE if it has either done nothing or the Event is not yet completely
    resolved.

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
    for etype in event.__class__.__mro__:
        for handler in registry.get(etype, ()):
            result = handler(event)
            if NOTDONE != result:
                return result

    return NOTDONE

