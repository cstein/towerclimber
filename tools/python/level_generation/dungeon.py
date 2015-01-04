import random

class Dungeon(object):
    """ Custom implementation of a binary space partition (BSP) like data structure to
        define procedurally generated dungeons.

        A dungeon is defined by the rooms that all leaf-nodes carry.
        Only leaf nodes may have a room.
    """

    # uniformness of new dungeons.
    # the closer to 0.5, the more uniform the size-distribution is
    _uniform = 0.3

    # discard-ratios of dungeons.
    # for height testing when splitting dungeons
    # NB: height testing below 2.0 is an error.
    #     use 2.2 as a minimum
    # larger values produces more variation in the accepted dungeons
    _ratio_h = 3.3

    # for width testing when splitting dungeons
    _ratio_w = 1.0 / _ratio_h

    # rate for the premature death of leafs. Dead leafs cannot split.
    # NB: death_rate increases with level as in
    # rate = _death_rate * _level
    _death_rate = 0.01
    _death_from_level = 5

    def __init__(self, x1, y1, x2, y2, level=0):
        self._x1 = x1
        self._y1 = y1
        self._x2 = x2
        self._y2 = y2
        self._level = level

        # some simple properties
        self._width = self._x2 - self._x1
        self._height = self._y2 - self._y1

        self._cx = self._x1 + 0.5 * self._width
        self._cy = self._y1 + 0.5 * self._height

        # leaf dungeons. if both are none, this is a leaf itself
        self.r = None
        self.l = None

        # room is the actual room
        self.room = None

        # a dead leaf cannot split
        self._isdead = False

        if self._ratio_h <= 2.0:
            raise ValueError("_ratio_h has a value equal to or less than 2.0. aborting.")

    def __str__(self):
        s = self._level*"  "
        s = s + "R[{0}] {1:6.2f} -> {3:6.2f} | {2:6.2f} -> {4:6.2f} [{5:6.2f}, {6:6.2f}] :: {7:6.2f}".format(self._level, self._x1, self._y1,
                                                                                                      self._x2, self._y2,
                                                                                                      self._width, self._height,
                                                                                                      self._GetRatio())
        if not self.IsLeaf():
            s += "\n{0:s}".format(str(self.l))
            s += "\n{0:s}".format(str(self.r))
        return s

    def IsLeaf(self):
        return self.r is None and self.l is None

    def DoKill(self):
        self._isdead = True

    def IsDead(self):
        return self._isdead

    def _Split(self):
        """ Performs the actual splitting
        """
        scale = random.uniform(self._uniform, 1.0 - self._uniform)
        vx = self._x1 + round(self._width * scale, 0)
        vy = self._y1 + round(self._height * scale, 0)
        if random.randint(0,1) == 0:
            # vertical split
            self.l = Dungeon(self._x1, self._y1, vx, self._y2, self._level +1)
            self.r = Dungeon(vx, self._y1, self._x2, self._y2, self._level +1)
            if self.l._GetRatio() < self._ratio_w or self.r._GetRatio() < self._ratio_w:
                self._Split()
        else:
            # horizontal split
            self.l = Dungeon(self._x1, self._y1, self._x2, vy, self._level +1)
            self.r = Dungeon(self._x1, vy, self._x2, self._y2, self._level +1)
            if self.l._GetRatio() > self._ratio_h or self.r._GetRatio() > self._ratio_h:
                self._Split()

    def _GetRatio(self):
        return self._width / self._height

    def Split(self, nlevel):
        """ Splits this dungeon into two.
            if the current split is the last split, create a room.

            several rules can cause this process to stop:

            depth: the level of tesselation has been reached
            death: premature death of the dungeon
        """
        if self._level == nlevel:
            self.room = SquareRoom( self._x1, self._y1, self._x2, self._y2 )
            self.DoKill()

        if random.random() < self._death_rate * self._level and self._level >= self._death_from_level :
            self.DoKill()

        if self.IsDead():
            return

        self._Split()
        self.l.Split(nlevel)
        self.r.Split(nlevel)

    def SetRatio(self, ratio_h):
        if ratio_h <= 2.0:
            raise ValueError("Ratio cannot have a value less than 2.0")
        self._ratio_h = ratio_h
        self._ratio_w = 1.0 / ratio_h

class Room(Dungeon):
    def __init__(self, x1, y1, x2, y2):
        Dungeon.__init__(self, x1, y1, x2, y2)
        self.DoKill()

    def IsLeaf(self):
        return True

class SquareRoom(Room):
    def __init__(self, x1, y1, x2, y2):
        Room.__init__(self, x1, y1, x2, y2)

        padding_factor = 0.0
        padding_offset = 2.0
        padding_w = int(self._width * padding_factor)
        padding_h = int(self._height * padding_factor)
        self._x1 = self._x1 + random.randint(0, padding_w) +padding_offset
        self._x2 = self._x2 - random.randint(0, padding_w) -padding_offset
        self._y1 = self._y1 + random.randint(0, padding_h) +padding_offset
        self._y2 = self._y2 - random.randint(0, padding_h) -padding_offset
