import pytest


from roglick.engine.ecs import Component


def test_component_slots():
    """Make sure Component objects don't accept arbitrary attributes

    To help with performance and reduce memory usage, Component objects are
    defined with the __slots__ parameter, which restricts them to only being
    able to store what attributes we explicitly define in said parameter.
    """

    c1 = Component()
    with pytest.raises(AttributeError):
        c1.foo = 'bar'

