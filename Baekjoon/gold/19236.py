from typing import cast
from copy import deepcopy


class Direction:
    delta = [-1, -1, 0, 1, 1, 1, 0, -1]

    def __init__(self, idx: int):
        self.idx = idx % len(self.delta)

    @property
    def dx(self):
        return self.delta[self.idx]

    @property
    def dy(self):
        return self.delta[(self.idx - 2) % len(self.delta)]

    def rotateCCW(self) -> "Direction":
        return Direction(self.idx + 1)


SIZE = 4


def getMaxFishCount(
    fishDir: list[list[Direction]],
    fishPos: list[tuple[int, int] | None],
    fishNum: list[list[int | None]],
    sharkPos: tuple[int, int],
    sharkDir: Direction,
) -> int:
    # fish moves
    for num in range(len(fishPos)):
        pos = fishPos[num]
        if pos is None:  # dead
            continue

        i, j = pos

        for _ in range(8):
            ni = i + fishDir[i][j].dx
            nj = j + fishDir[i][j].dy

            if 0 <= ni < SIZE and 0 <= nj < SIZE and (ni, nj) != sharkPos:
                target = fishNum[ni][nj]

                fishNum[i][j], fishNum[ni][nj] = fishNum[ni][nj], fishNum[i][j]
                fishDir[i][j], fishDir[ni][nj] = fishDir[ni][nj], fishDir[i][j]
                fishPos[num] = (ni, nj)

                if target is not None:
                    fishPos[target] = (i, j)

                break

            fishDir[i][j] = fishDir[i][j].rotateCCW()

    # shark moves
    ret = 0

    i, j = sharkPos
    while True:
        i += sharkDir.dx
        j += sharkDir.dy

        if not (0 <= i < SIZE and 0 <= j < SIZE):
            break

        targetNum = fishNum[i][j]
        if targetNum is None:
            continue
        targetDir = fishDir[i][j]

        fishNum[i][j] = None
        fishPos[targetNum] = None

        ret = max(
            ret,
            getMaxFishCount(
                deepcopy(fishDir),
                deepcopy(fishPos),
                deepcopy(fishNum),
                (i, j),
                targetDir,
            )
            + targetNum
            + 1,
        )

        fishNum[i][j] = targetNum
        fishPos[targetNum] = (i, j)

    return ret


def solve():
    fishDir: list[list[Direction]] = [[Direction(0)] * 4 for _ in range(4)]
    fishPos: list[tuple[int, int] | None] = [None] * 16
    fishNum: list[list[int | None]] = [[None] * 4 for _ in range(4)]

    for i in range(4):
        line = list(map(int, input().split()))
        for j in range(0, 4):
            num = line[j << 1] - 1

            fishNum[i][j] = num
            fishPos[num] = (i, j)

            fishDir[i][j] = Direction(line[j << 1 | 1] - 1)

    num = cast(int, fishNum[0][0])
    fishPos[num] = None
    fishNum[0][0] = None
    sharkDir = fishDir[0][0]

    print(getMaxFishCount(fishDir, fishPos, fishNum, (0, 0), sharkDir) + num + 1)


solve()
