import json


_SKILL_TREE = {}


class SkillTreeNode(object):
    def __init__(self, name, key, attr, parent):
        self._name = name
        self._key = key
        self._attr = attr
        self._parent = parent

    @property
    def name(self):
        return self._name

    @property
    def key(self):
        return self._key

    @property
    def attr(self):
        return self._attr

    @property
    def parent(self):
        if self._parent is None:
            return None
        else:
            return _SKILL_TREE[self._parent]

    def __repr__(self):
        return "{cls}({skill})".format(
                cls=self.__class__.__name__,
                skill=self.name)


def _make_key(parent, child):
    child = child.lower().replace(' ', '_')
    if parent:
        return parent + '.' + child
    else:
        return child

def _process_skill_list(skills, parent_key=None):
    for skill in skills:
        key = _make_key(parent_key, skill['name'])
        _SKILL_TREE[key] = SkillTreeNode(
                name=skill['name'],
                key=key,
                attr=skill['attr'],
                parent=parent_key)
        _process_skill_list(skill['child_skills'], key)

def _build_skill_tree():
    with open('data/skills.json') as fh:
        data = json.load(fh)

    _process_skill_list(data)
_build_skill_tree()


def get(skill):
    return _SKILL_TREE[skill]


