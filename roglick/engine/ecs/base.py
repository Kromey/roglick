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


class SystemBase(object):
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

