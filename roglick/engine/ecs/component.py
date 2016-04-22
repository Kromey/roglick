class ComponentMeta(type):
    """Metaclass that builds a Component class.

    This class transforms the _properties class property into a __slots__
    property on the class before it is created, which suppresses the normal
    creation of the __dict__ property and the memory overhead that brings.
    """
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
        keyword arguments. The _properties property should be a tuple of
        2-tuples in the form (k,v), where k is the property name and v is the
        property's default value; positional initialization follows the same
        order as _properties.
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

    def __repr__(self):
        values = []
        for k, default in self._properties:
            values.append("{k}={v}".format(k=k, v=getattr(self, k)))

        values = ", ".join(values)

        return "{cls}({values})".format(
                cls = self.__class__.__name__,
                values = values)


class MultiComponentMeta(ComponentMeta):
    """Metaclass that builds a MultiComponent class.

    This class is responsible for creating and assigning the "sub-component"
    class as a class property of the new MultiComponent subclass.
    """
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

    A Component class will be automatically created using the _properties
    property; by default the name will be derived by removing the "Component"
    suffix as well as any trailing 's' characters left (e.g. SkillsComponent
    would have a Component named Skill), but this can be overridden with a
    _component_name property in the class definition. The Component will then
    be available as a class property of the MultiComponent class.

    For example, a SkillsComponent class that subclasses MultiComponentBase by
    default will result in the creation of the SkillsComponent.Skill Component
    class. An InventoryComponent class with a _component_name property of
    'Item' will instead result in the creation of the InventoryComponent.Item
    Component class.
    """
    _properties = ()


