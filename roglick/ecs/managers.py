from .base import Component, Entity
from .exceptions import NoComponentForEntityError, NotAComponentError


class EntityManager(object):
    """The EntityManager is responsible for creating and maintaining Entities

    It accomplishes its job by creating monotonically increasing Entity IDs, as
    well as maintaining a list of all the Component managers which, in turn,
    keep track of all the Components.
    """
    def __init__(self):
        self._next_eid = 0
        self._components = {}

    def create_entity(self):
        """Creates and returns a new Entity."""
        entity = Entity(self._next_eid)
        self._next_eid += 1
        return entity

    def destroy_entity(self, entity):
        """Remove an Entity and all its Components.

        Since our only storage of Entities is as dictionary keys, it's
        sufficient to remove all Components for the Entity; if an Entity
        doesn't index any Components, for all intents and purposes it doesn't
        exist.
        """
        # We can't iterate directly over the dict, as we're modifying it
        ctypes = self._components.keys()
        for ctype in ctypes:
            # We already have logic to do this, so be DRY
            self.remove_component(entity, ctype)

    def set_component(self, entity, component):
        """Set the given Component for the Entity.

        This method will either add a new Component, or overwrite an existing
        one.
        """
        if not isinstance(component, Component):
            # Maybe an unnecessary throwback to my C++ version...
            raise NotAComponentError(component)

        ctype = type(component)
        # We need a dictionary for each type we store, so make sure we have one
        if ctype not in self._components:
            self._components[ctype] = {}

        self._components[ctype][entity] = component

    def get_component(self, entity, component_type):
        """Returns the Entity's Component or raises NoComponentForENtityError"""
        try:
            return self._components[component_type][entity]
        except KeyError:
            raise NoComponentForEntityError(entity, component_type)

    def remove_component(self, entity, component_type):
        """Removes the Entity's Component"""
        try:
            del self._components[component_type][entity]
            # Do we want to do anything if we remove the last one? Prolly not..
        except KeyError:
            # No Component to remove? Who cares, that's what we wanted! :)
            pass

