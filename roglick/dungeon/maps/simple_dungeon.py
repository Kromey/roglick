import roglick.lib.libtcodpy as libtcod


from roglick.dungeon.base import Map,Room,Tile
from roglick.dungeon import tiles


class SimpleDungeon(Map):
    def __init__(self, width, height, max_rooms=30, room_min_size=6, room_max_size=10):
        super().__init__(width, height)

        self._rooms = []

        self.make_map(max_rooms, room_min_size, room_max_size)

    @property
    def rooms(self):
        return self._rooms

    def make_map(self, max_rooms, room_min_size, room_max_size):
        for r in range(max_rooms):
            # Random width/height for room
            w = libtcod.random_get_int(0, room_min_size, room_max_size)
            h = libtcod.random_get_int(0, room_min_size, room_max_size)
            # Random x,y for room
            x = libtcod.random_get_int(0, 0, self.width - w -1)
            y = libtcod.random_get_int(0, 0, self.height - h -1)

            # Create the room
            new_room = Room(x, y, w, h)

            # Make sure it doesn't collide with any of our others
            intersects = False
            for other_room in self._rooms:
                if new_room.intersects(other_room):
                    intersects = True
                    break

            if not intersects:
                # Our new room is valid! Add it to our map!
                self.add_room(new_room)

    def add_room(self, room, fill=tiles.FloorTile):
        # Add this room to our list of rooms
        self._rooms.append(room)
        # Carve it out of the surrounding rock
        self.fill_room(room)

        # Now connect it to our previous room
        self.connect_last_rooms()

    def fill_room(self, room, fill=tiles.FloorTile):
        for x in range(room.x1 + 1, room.x2):
            for y in range(room.y1 + 1, room.y2):
                self.tiles[x][y] = Tile(**fill)

    def connect_last_rooms(self):
        if len(self._rooms) > 1:
            room1 = self._rooms[len(self._rooms)-2]
            room2 = self._rooms[len(self._rooms)-1]

            # Pick a random starting point in the first room
            x1 = libtcod.random_get_int(0, room1.x1, room1.x2)
            y1 = libtcod.random_get_int(0, room1.y1, room1.y2)
            # End in the second room
            x2 = libtcod.random_get_int(0, room2.x1, room2.x2)
            y2 = libtcod.random_get_int(0, room2.y1, room2.y2)

            # Now create a tunnel to connect them
            self.create_tunnel(x1, y1, x2, y2)

    def create_tunnel(self, x1, y1, x2, y2):
        # Flip a coin to decide if we go horizontal or vertical first
        if libtcod.random_get_int(0, 0, 1) == 1:
            self.create_h_tunnel(x1, x2, y1)
            self.create_v_tunnel(y1, y2, x2)
        else:
            self.create_v_tunnel(y1, y2, x1)
            self.create_h_tunnel(x1, x2, y2)

    def create_h_tunnel(self, x1, x2, y):
        for x in range(min(x1, x2), max(x1, x2) + 1):
            self.tiles[x][y] = Tile(**tiles.FloorTile)

    def create_v_tunnel(self, y1, y2, x):
        for y in range(min(y1, y2), max(y1, y2) + 1):
            self.tiles[x][y] = Tile(**tiles.FloorTile)

