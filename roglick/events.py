from roglick.engine.event import Event


class NewMapEvent(Event):
    pass


class QuitEvent(Event):
    pass


class PreInputEvent(Event):
    pass


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


class ActionCompleteEvent(Event):
    def __init__(self, entity, fatigue_cost, apply_speed=True):
        super().__init__(entity=entity)

        self.fatigue_cost = fatigue_cost
        self.apply_speed = apply_speed

    def __repr__(self):
        if self.apply_speed:
            # Don't bother with apply_speed parameter if it's still default
            return "{cls}({e}, {cost})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    cost=self.fatigue_cost)
        else:
            return "{cls}({e}, {cost}, False)".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    cost=self.fatigue_cost)

