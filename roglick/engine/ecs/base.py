from itertools import zip_longest


class Entity(object):
    """An Entity is really little more than a lookup key for Components"""
    __slots__ = ("_eid",)

    def __init__(self, eid):
        self._eid = eid

    def __repr__(self):
        return "{name}({eid})".format(
                name=type(self).__name__,
                eid=self._eid)

    def __hash__(self):
        return self._eid

    def __eq__(self, rhs):
        return hash(self) == hash(rhs)


class Component(object):
    """Base class for Components to inherit from.

    Components should primarily just be data containers; logic should live
    elsewhere, mostly in Systems."""
    __slots__ = ()
    pass


def multi_component(name, properties, component_name=None):
    """Generate a "multi-component" container and matching sub-component.

    Multi-components provide dict-like access to a simple Component defined
    with the properties named in component_properties. If provided, values in
    component_defaults are applied, in order, as default values to each property,
    with the value None used to initialize any property for which a default is
    not provided.
    """
    if component_name is None:
        # Generate the name of the sub-component by stripping off "Component"
        # from the container's name
        component_name = name.replace('Component','')
        # Take off a trailing 's', too; (usually) turns plural to singular
        if component_name.endswith('s'):
            component_name = component_name[:-1]

    # This will be the __init__() method for the sub-component
    def component_init(self, *args, **kwargs):
        # Start by initializing our properties to default values
        for k,v in properties:
            setattr(self, k, v)

        # For any positional arguments, assign those values to our properties
        # This is done in order of our __slots__ property
        for k,v in zip(self.__slots__, args):
            setattr(self, k, v)
        # For any keyword arguments, assign those values to our properties
        # Keywords must of course match one of our properties
        for k in kwargs:
            setattr(self, k, kwargs[k])

    # Extract the property names from our properties, these are our slots
    slots = tuple([p[0] for p in properties])

    # Generate the class for our sub-component, using the provided slots
    # and the above init method.
    component = type(component_name,
            (Component,),
            {'__slots__': slots, '__init__': component_init})

    # Now create a container providing dict-style access to components
    return type(name,
            (Component, dict),
            {component_name: component})


class System(object):
    """Systems are the workhorses of the ECS architecture.

    A System takes care of the actual execution of game logic, each one being
    responsible for implementing a concrete subset of the game's overall rules.
    """
    def __init__(self):
        self._entity_manager = None
        self._world = None

    def set_entity_manager(self, entity_manager):
        self._entity_manager = entity_manager

    def set_world_manager(self, world_manager):
        self._world = world_manager

    def execute(self):
        """Execute this system on its EntityManager."""
        pass

