import json
from glob import glob


from roglick.engine import random


class FileObj(object):
    def __init__(self, conf_file, obj_key=None):
        self._data = {}
        self._load_file(conf_file, obj_key)

    def keys(self):
        return self._data.keys()

    def random(self, rand=None):
        if rand is None:
            rand = random

        return self[rand.choice(list(self.keys()))]

    def _load_file(self, conf_file, obj_key=None):
        with open(conf_file) as fh:
            data = json.load(fh)

        if obj_key is not None:
            data = data[obj_key]

        for key,item in self._process_data(data):
            self._data[key] = item

    def _make_key(self, item):
        try:
            return item['name'].lower().replace(' ', '_')
        except KeyError:
            return len(self._data)

    def _process_data(self, data):
        if isinstance(data, dict):
            key = self._make_key(data)
            yield key,self._process_item(data)
        else:
            for item in data:
                key = self._make_key(item)
                yield key,self._process_item(item)

    def _process_item(self, item):
        return item

    def __getitem__(self, key):
        return self._data[key]

    def __getattr__(self, key):
        return self[key]

    def __len__(self):
        return len(self._data)

    def __iter__(self):
        return iter(self._data)

    def __contains__(self, item):
        for key in self:
            if item == self[key]:
                return True

        return False


class MultiFileObj(FileObj):
    def _load_file(self, file_pattern, obj_key=None):
        for conf_file in glob(file_pattern):
            super()._load_file(conf_file, obj_key)

