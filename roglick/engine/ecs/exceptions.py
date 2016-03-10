

class NoComponentForEntityError(Exception):
    """Exception raised when an Entity does not have this Component"""
    def __init__(self, entity, component_type):
        super().__init__("{entity} has no {component_type}".format(
            entity=entity, component_type=component_type))


class NotAComponentError(Exception):
    """Exception raised when using a component that doesn't subclass Component
    """
    def __init__(self, obj):
        super().__init__("{obj} is of type {kind} instead of Component".format(
            obj=obj, kind=type(obj).__name__))

