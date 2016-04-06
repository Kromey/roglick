import collections


from roglick.engine.event import Event


class SkillCheckEvent(Event):
    Result = collections.namedtuple(
            'Result',
            ['success', 'critical', 'roll', 'dos'])

    def __init__(self, entity, skill, modifier=0):
        super().__init__(entity=entity)

        self.skill = skill
        self.modifier = modifier
        self.result = None

    def __repr__(self):
        if self.result is None:
            return "{cls}({e}, {s}, {m:+})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    s=self.skill,
                    m=self.modifier)
        else:
            return "{cls}({e}, {s}, {m:+}, {r})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    s=self.skill,
                    m=self.modifier,
                    r=self.result)
