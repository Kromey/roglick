from roglick.engine.ecs import ComponentBase


class FoVComponent(ComponentBase):
    _properties = (('x', None), ('y', None), ('fov', None))

