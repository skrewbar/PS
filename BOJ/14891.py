from typing import Iterable


class Gear:
    def __init__(self, poles: Iterable[int]):
        """
        poles should satisfy the following conditions:

        0 represents N pole and 1 represents S pole.
        poles[0] represents the pole of the upmost tooth.
        poles[i] represents the pole of the i-th tooth clockwise from the 0-th tooth.
        """

        self.poles = tuple(poles)
        self.idx = 6

    @property
    def leftPole(self):
        return self.poles[self.idx]

    @property
    def rightPole(self):
        return self.poles[(self.idx + 4) % 8]

    @property
    def upPole(self):
        return self.poles[(self.idx + 2) % 8]

    def rotateClockwise(self):
        self.idx = (self.idx - 1) % 8

    def rotateCounterclockwise(self):
        self.idx = (self.idx + 1) % 8


gears = [Gear(map(int, list(input()))) for _ in range(4)]

K = int(input())
for _ in range(K):
    num, direction = map(int, input().split())
    num -= 1

    rotate = [0] * 4
    rotate[num] = direction

    for i in range(num - 1, -1, -1):
        if gears[i].rightPole != gears[i + 1].leftPole and rotate[i + 1]:
            rotate[i] = -rotate[i + 1]
    for i in range(num + 1, 4):
        if gears[i - 1].rightPole != gears[i].leftPole and rotate[i - 1]:
            rotate[i] = -rotate[i - 1]

    for i in range(4):
        if rotate[i] == 1:
            gears[i].rotateClockwise()
        elif rotate[i] == -1:
            gears[i].rotateCounterclockwise()

score = 0
weight = 1
for i in range(4):
    if gears[i].upPole == 1:
        score += weight
    weight <<= 1

print(score)
