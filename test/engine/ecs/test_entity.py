from roglick.engine.ecs import Entity


def test_entity_equality():
    e1 = Entity(1)
    e2 = Entity(1)

    # Different objects...
    assert id(e1) != id(e2)
    # ...but same Entity
    assert e1 == e2

def test_entity_unequality():
    e1 = Entity(1)
    e2 = Entity(2)

    # Different objects...
    assert id(e1) != id(e2)
    # ...and different Entities
    assert e1 != e2

