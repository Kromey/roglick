from roglick.engine.event import Event


class MoveEvent(Event):
    def __init__(self, entity, dx, dy):
        super().__init__(entity=entity)

        self.dx = dx
        self.dy = dy

    def __repr__(self):
        return "{cls}({e}, {dx}, {dy})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                dx=self.dx,
                dy=self.dy)


class ClimbEvent(Event):
    pass


class ClimbDownEvent(ClimbEvent):
    pass


class ClimbUpEvent(ClimbEvent):
    pass

