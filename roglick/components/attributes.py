from roglick.engine.ecs import ComponentBase


class AttributesComponent(ComponentBase):
    _properties = (('st', 10), ('dx', 10), ('iq', 10), ('pe', 10))

