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

def test_entity_dict_index():
    """Test that our Entity object can be used for dict keys

    By default, user-created objects are hashed based on id, meaning that no
    two different objects will ever reference the same data if used as dict
    keys. Therefore, if we can correctly store and retrieve data using
    different objects but which are logically the same, then we know that our
    overridden __hash__ method is working correctly and properly enabled dict
    access.
    """
    data = {}
    for x in range(10):
        data[Entity(x)] = x

    for x in range(10):
        assert data[Entity(x)] == x

    # Also ensure we can correctly access and modify Entity-keyed dict data
    for x in range(10):
        data[Entity(x)] = 2*x

    for x in range(10):
        assert data[Entity(x)] == 2*x

