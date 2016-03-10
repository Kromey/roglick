from roglick.engine.event import Event


class MoveEvent(Event):
    def __init__(self, entity, dx, dy):
        super().__init__(entity_source=entity)

        self.dx = dx
        self.dy = dy

