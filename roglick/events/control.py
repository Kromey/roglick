from roglick.engine.event import Event


class NewMapEvent(Event):
    pass


class MapChangedEvent(Event):
    pass


class QuitEvent(Event):
    pass


class PreInputEvent(Event):
    pass


class MessageEvent(Event):
    def __init__(self, msg):
        super().__init__(entity=None)

        self.msg = msg

    def __repr__(self):
        return "{cls}({msg})".format(
                cls=self.__class__.__name__,
                msg=self.msg)

