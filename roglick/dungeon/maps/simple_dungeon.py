from roglick.dungeon.base import Map,Room,Tile
from roglick.dungeon import tiles


class SimpleDungeon(Map):
    def __init__(self, width, height, random, *args, **kwargs):
        super().__init__(width, height, random)

        self.make_map(*args, **kwargs)

    @property
    def rooms(self):
        return self._rooms

    def make_map(self, max_rooms=50, room_min_size=6, room_max_size=10):
        super().make_map()

        self._rooms = []

        for r in range(max_rooms):
            # Random width/height for room
            w = self._random.get_int(room_min_size, room_max_size)
            h = self._random.get_int(room_min_size, room_max_size)
            # Random x,y for room
            x = self._random.get_int(0, self.width - w -1)
            y = self._random.get_int(0, self.height - h -1)

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

        self.connect_rooms()

    def add_room(self, room, fill=tiles.FloorTile):
        # Add this room to our list of rooms
        self._rooms.append(room)
        # Carve it out of the surrounding rock
        self.fill_room(room)

        # Now connect it to our previous room
        #self.connect_last_rooms()

    def fill_room(self, room, fill=tiles.FloorTile):
        for x in range(room.x1 + 1, room.x2):
            for y in range(room.y1 + 1, room.y2):
                self.tiles[x][y] = Tile(**fill)

    def connect_rooms(self):
        for i in range(len(self._rooms)):
            room = self._rooms[i]
            rx,ry = room.center
            # Initialize distance to a value bigger than anything possible
            d2 = (self.width * self.height)**2

            for j in range(i+1, len(self._rooms)):
                ox,oy = self._rooms[j].center
                i_d2 = self.distance_squared(rx, ry, ox, oy)
                if i_d2 < d2:
                    other = self._rooms[j]
                    d2 = i_d2

            # other is now the nearest room. Connect them.
            # Pick a random starting point in the first room
            x1 = self._random.get_int(room.x1+1, room.x2-1)
            y1 = self._random.get_int(room.y1+1, room.y2-1)
            # End in the second room
            x2 = self._random.get_int(other.x1+1, other.x2-1)
            y2 = self._random.get_int(other.y1+1, other.y2-1)

            # Now create a tunnel to connect them
            self.create_tunnel(x1, y1, x2, y2)

    def connect_last_rooms(self):
        if len(self._rooms) > 1:
            room1 = self._rooms[len(self._rooms)-2]
            room2 = self._rooms[len(self._rooms)-1]

            # Pick a random starting point in the first room
            x1 = self._random.get_int(room1.x1+1, room1.x2-1)
            y1 = self._random.get_int(room1.y1+1, room1.y2-1)
            # End in the second room
            x2 = self._random.get_int(room2.x1+1, room2.x2-1)
            y2 = self._random.get_int(room2.y1+1, room2.y2-1)

            # Now create a tunnel to connect them
            self.create_tunnel(x1, y1, x2, y2)

