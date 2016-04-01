from roglick.engine import file_obj


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


class SkillTree(file_obj.FileObj):
    def __init__(self):
        super().__init__('data/skills.json')

    def _process_data(self, skills, parent_key=None):
        for skill in skills:
            key = self._make_key(skill, parent_key)
            node = SkillTreeNode(
                    name=skill['name'],
                    key=key,
                    attr=skill['attr'],
                    parent=parent_key)
            yield key,node

            for key,node in self._process_data(skill['child_skills'], key):
                yield key,node

    def _make_key(self, skill, parent_key=None):
        key = super()._make_key(skill)

        if parent_key:
            return '.'.join((parent_key, key))
        else:
            return key


_SKILL_TREE = SkillTree()

