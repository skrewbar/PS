from typing import cast


class Direction:
    delta = [-1, 1, 0, 0]

    def __init__(self, idx: int):
        self.idx = idx % len(self.delta)

    @property
    def dx(self):
        return self.delta[self.idx]

    @property
    def dy(self):
        return self.delta[(self.idx + 2) % len(self.delta)]


def getDirFromDelta(dx: int, dy: int):
    if dx != 0:
        return Direction(Direction.delta.index(dx))
    else:
        return Direction(Direction.delta.index(dy) - 2)


def solve():
    N, M, k = map(int, input().split())

    remainTime = [[0] * N for _ in range(N)]
    smellNum: list[list[int | None]] = [[None] * N for _ in range(N)]

    sharkNum: list[list[int | None]] = [[None] * N for _ in range(N)]
    for i in range(N):
        line = list(map(int, input().split()))
        for j in range(N):
            if line[j] == 0:
                continue

            sharkNum[i][j] = line[j] - 1
            remainTime[i][j] = k
            smellNum[i][j] = sharkNum[i][j]

    sharkDir = [Direction(d - 1) for d in map(int, input().split())]

    priorities: list[list[list[Direction]]] = [[[] for _ in range(4)] for _ in range(M)]
    for i in range(M):
        for j in range(4):
            priorities[i][j] = list(
                map(lambda x: Direction(int(x) - 1), input().split())
            )

    t = 1
    while t <= 1000:
        newSharkNum: list[list[int | None]] = [[None] * N for _ in range(N)]
        for i in range(N):
            for j in range(N):
                num = sharkNum[i][j]

                if num is None:
                    continue

                nowDir = sharkDir[num]

                noSmell: tuple[int, int] | None = None
                mySmell: tuple[int, int] | None = None

                for d in priorities[num][nowDir.idx]:
                    ni = i + d.dx
                    nj = j + d.dy

                    if 0 <= ni < N and 0 <= nj < N:
                        if smellNum[ni][nj] is None:
                            noSmell = (ni, nj)
                            break
                        elif smellNum[ni][nj] == num and mySmell is None:
                            mySmell = (ni, nj)

                moveTo = noSmell if noSmell is not None else mySmell
                assert moveTo is not None

                ni, nj = moveTo

                if newSharkNum[ni][nj] is None or num < cast(int, newSharkNum[ni][nj]):
                    newSharkNum[ni][nj] = num
                    sharkDir[num] = getDirFromDelta(ni - i, nj - j)

        sharkNum = newSharkNum
        maxNum = 0

        for i in range(N):
            for j in range(N):
                if sharkNum[i][j] is not None:
                    maxNum = max(maxNum, cast(int, sharkNum[i][j]))
                    remainTime[i][j] = k
                    smellNum[i][j] = sharkNum[i][j]
                    continue

                if remainTime[i][j] == 0:
                    continue

                remainTime[i][j] -= 1
                if remainTime[i][j] == 0:
                    smellNum[i][j] = None

        if maxNum == 0:
            break

        t += 1

    print(t if t <= 1000 else -1)


solve()
