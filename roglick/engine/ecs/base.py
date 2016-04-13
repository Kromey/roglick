

class Entity(object):
    """An Entity is really little more than a lookup key for Components"""
    __slots__ = ("_eid")

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


class MultiComponent(Component):
    """Base class for dict-like access to multiple Components."""
    __slots__ = ('_data',)
    def init(self):
        self._data = {}

    def __getitem__(self, key):
        return self._data[key]

    def __setitem__(self, key, value):
        self._data[key] = value


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

