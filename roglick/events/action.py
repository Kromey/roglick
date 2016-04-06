from roglick.engine.event import Event


class OpenDoorEvent(Event):
    def __init__(self, entity, x, y):
        super().__init__(entity=entity)

        self.x = x
        self.y = y

    def __repr__(self):
        return "{cls}({e}, {x}, {y})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                x=self.x,
                y=self.y)


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

