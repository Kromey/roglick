from .base import Entity


class EntityManager(object):
    """The EntityManager is responsible for creating and maintaining Entities

    It accomplishes its job by creating monotonically increasing Entity IDs, as
    well as maintaining a list of all the Component managers which, in turn,
    keep track of all the Components.
    """
    def __init__(self):
        self._next_eid = 0
        self._managers = {}

    def create_entity(self):
        entity = Entity(self._next_eid)
        self._next_eid += 1
        return entity

