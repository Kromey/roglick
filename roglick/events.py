from roglick.engine.event import Event


class QuitEvent(Event):
    def __repr__(self):
        return self.__class__.__name__


class PreInputEvent(Event):
    def __repr__(self):
        return self.__class__.__name__


class MoveEvent(Event):
    def __init__(self, entity, dx, dy):
        super().__init__(entity_source=entity)

        self.dx = dx
        self.dy = dy

    def __repr__(self):
        return "{cls}({e}, {dx}, {dy})".format(
                cls=self.__class__.__name__,
                e=self.entity_source,
                dx=self.dx,
                dy=self.dy)

