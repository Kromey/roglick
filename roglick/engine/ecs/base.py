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


class ComponentMeta(type):
    def __new__(cls, name, bases, namespace, **kwargs):
        slots = tuple([p[0] for p in namespace['_properties']])

        # Define our class's slots
        namespace['__slots__'] = slots

        # Generate the class for our component
        return type.__new__(cls,
                name,
                bases,
                namespace)


class ComponentBase(object, metaclass=ComponentMeta):
    """Base class for Components to inherit from.

    Components should primarily just be data containers; logic should live
    elsewhere, mostly in Systems."""
    __slots__ = ()
    _properties = ()

    def __init__(self, *args, **kwargs):
        """A generic init method for initializing properties.

        Properties can be set on initialization via either positional or
        keyword arguments. The _default_values class member should be the same
        length as __slots__, as it provides default values to members in left
        to right order -- the same order as positional arguments.
        """
        # Start by initializing our properties to default values
        for k,v in self._properties:
            setattr(self, k, v)

        # For any positional arguments, assign those values to our properties
        # This is done in order of our __slots__ property
        for k,v in zip(self.__slots__, args):
            setattr(self, k, v)
        # For any keyword arguments, assign those values to our properties
        # Keywords must of course match one of our properties
        for k in kwargs:
            setattr(self, k, kwargs[k])


class MultiComponentMeta(ComponentMeta):
    def __new__(cls, name, bases, namespace, **kwargs):
        try:
            component_name = namespace['_component_name']
        except KeyError:
            # Generate the name of the sub-component by stripping off "Component"
            # from the container's name. Also remove trailing 's'.
            component_name = name.replace('Component','').rstrip('s')

        namespace[component_name] = type(component_name,
                (ComponentBase,),
                {'_properties': namespace['_properties']})

        # Now create our container
        return type.__new__(cls,
                name,
                bases,
                namespace)


class MultiComponentBase(dict, ComponentBase, metaclass=MultiComponentMeta):
    """Base class for MultiComponents to inherit from.

    MultiComponent are dict-style containers for Components, allowing a single
    Entity to have multiple instance of the Component.
    """
    _properties = ()


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

