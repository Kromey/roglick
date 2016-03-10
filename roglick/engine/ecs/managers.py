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

        # Since it's common enough, we'll go ahead and create an Entity for the
        # player's character right away; no harm if it's not used
        self._pc = self.create_entity()

    @property
    def pc(self):
        return self._pc

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

    def get_entities_with_component(self, component_type):
        """Get an iterable of all Entities with the specified Component

        Returns an iterable of tuples of the form (Entity, ComponentDict);
        ComponentDict is a dict object indexed by the Component type.
        """
        try:
            for entity in self._components[component_type]:
                yield entity, {component_type: self._components[component_type][entity]}
        except KeyError:
            pass

    def get_entities_with_components(self, component_types):
        """As get_entities_with_components, but takes an iterable of Components

        The returned iterable contains only Entities that have all of the
        Components listed in component_types.
        """
        if 1 == len(component_types):
            for e,c in self.get_entities_with_component(component_types[0]):
                yield e,c
        else:
            for entity, components in self.get_entities_with_components(component_types[1:]):
                try:
                    components[component_types[0]] = self._components[component_types[0]][entity]
                    yield entity, components
                except KeyError:
                    pass


class SystemManager(object):
    """Container and manager for Systems."""
    def __init__(self, entity_manager):
        """Create a new SystemManager for the given EntityManager"""
        self._entity_manager = entity_manager
        self._systems = []

    def add_system(self, system):
        """Add the System to this SystemManager.

        The System will automatically have its EntityManager updated to that of
        this SystemManager.
        """
        system.set_entity_manager(self._entity_manager)
        self._systems.append(system)

    def create_system(self, system_type):
        """Instantiate a System of the supplied type, then add it.

        This shortcut is useful for Systems that require no additional setup.
        """
        system = system_type()
        # Why reinvent the wheel? We already know how to add Systems...
        self.add_system(system)

    def execute(self):
        """Execute all Systems in the order they were added."""
        for system in self._systems:
            system.execute()

