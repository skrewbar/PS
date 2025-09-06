from enum import Enum

delta = [1, 0, -1, 0]


class Direction(Enum):
    RIGHT = 0
    UP = 1
    LEFT = 2
    DOWN = 3

    @property
    def dx(self):
        return delta[self.value]

    @property
    def dy(self):
        return delta[3 - self.value]

    def rotatedCCW(self):
        return Direction((self.value + 1) % 4)


class DragonCurve:
    def __init__(self, x: int, y: int, d: Direction, g: int):
        self.x = x
        self.y = y

        if g == 0:
            self.curves = [d]
            return

        curves = DragonCurve(0, 0, d, g - 1).curves
        nextCurves = list(map(lambda c: c.rotatedCCW(), curves[::-1]))

        self.curves = curves + nextCurves

    def draw(self, grid: list[list[bool]]):
        x, y = self.x, self.y
        grid[x][y] = True

        for d in self.curves:
            x += d.dx
            y += d.dy
            grid[x][y] = True


grid = [[False] * 101 for _ in range(101)]

N = int(input())

for _ in range(N):
    x, y, d, g = map(int, input().split())
    DragonCurve(x, y, Direction(d), g).draw(grid)

ans = 0
for i in range(100):
    for j in range(100):
        if all((grid[i][j], grid[i + 1][j], grid[i][j + 1], grid[i + 1][j + 1])):
            ans += 1

print(ans)
