from enum import Enum
from typing import Self
import sys

input = lambda: sys.stdin.readline().rstrip()

r, c, m = map(int, input().split())


class Direction(Enum):
    UP = (-1, 0)
    DOWN = (1, 0)
    RIGHT = (0, 1)
    LEFT = (0, -1)

    @classmethod
    def int_to_dir(cls, x: int) -> Self:
        match x:
            case 1:
                return cls.UP
            case 2:
                return cls.DOWN
            case 3:
                return cls.RIGHT
            case 4:
                return cls.LEFT
        raise Exception(f"Cannot convert {x} to Direction")

    @property
    def dx(self):
        return self.value[0]

    @property
    def dy(self):
        return self.value[1]


class Shark:
    def __init__(self, pos: tuple[int, int], speed: int, dir: Direction, size: int):
        self.pos = pos
        self.dx = dir.dx * speed
        self.dy = dir.dy * speed
        self.size = size

    def __hash__(self):
        """상어의 크기는 서로 다르므로 해시값으로 사용 가능"""
        return self.size

    def move(self):
        x, y = self.pos
        x += self.dx
        y += self.dy

        while not (0 <= x < r and 0 <= y < c):
            if x < 0:
                x = abs(x)
                self.dx = -self.dx
            if y < 0:
                y = abs(y)
                self.dy = -self.dy
            if x >= r:
                x = 2 * r - x - 2
                self.dx = -self.dx
            if y >= c:
                y = 2 * c - y - 2
                self.dy = -self.dy
        self.pos = (x, y)


sharkset: set[Shark] = set()
for _ in range(m):
    x, y, speed, dir, size = map(int, input().split())
    x -= 1
    y -= 1
    sharkset.add(Shark((x, y), speed, Direction.int_to_dir(dir), size))


ans = 0
for j in range(c):
    pos_to_shark: dict[tuple[int, int], Shark] = {}
    for shark in sharkset:
        pos_to_shark[shark.pos] = shark

    for i in range(r):
        if (i, j) in pos_to_shark:
            shark = pos_to_shark[(i, j)]
            ans += shark.size
            sharkset.remove(shark)
            break

    for shark in sharkset:
        shark.move()

    pos_to_shark.clear()
    for shark in sharkset.copy():
        if shark.pos not in pos_to_shark:
            pos_to_shark[shark.pos] = shark
            continue

        if shark.size > pos_to_shark[shark.pos].size:
            sharkset.remove(pos_to_shark[shark.pos])
            pos_to_shark[shark.pos] = shark
        else:
            sharkset.remove(shark)

    # board = [["."] * c for _ in range(r)]
    # for shark in sharkset:
    #     board[shark.pos[0]][shark.pos[1]] = shark.size
    # for row in board:
    #     print(*row, sep="")
    # print(ans)

print(ans)
