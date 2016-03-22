import json


SKILL_TREE = {}


class SkillTreeNode(object):
    def __init__(self, attr, parent):
        self._attr = attr
        self._parent = parent

    @property
    def attr(self):
        return self._attr

    @property
    def parent_name(self):
        return self._parent

    @property
    def parent(self):
        if self._parent is None:
            return None
        else:
            return SKILL_TREE[self._parent]

    def __repr__(self):
        parent = self.parent
        if parent is None:
            return "{cls}({attr})".format(
                    cls=self.__class__.__name__,
                    attr=self.attr)
        else:
            return "{cls}({attr}, {parentname}:{parentnode})".format(
                    cls=self.__class__.__name__,
                    attr=self.attr,
                    parentname=self.parent_name,
                    parentnode=parent)


def _build_skill_tree():
    with open('data/skills.json') as fh:
        data = json.load(fh)

    for skill in data:
        SKILL_TREE[skill] = SkillTreeNode(**data[skill])
_build_skill_tree()


def get(skill):
    return SKILL_TREE[skill]


