import sys
from enum import Enum

input = lambda: sys.stdin.readline().rstrip()


class Direction(Enum):
    LEFT = 0
    RIGHT = 1


INF = int(1e9)


N, M, H = map(int, input().split())

line: list[list[Direction | None]] = [[None] * H for _ in range(N)]

for _ in range(M):
    a, b = map(lambda x: int(x) - 1, input().split())

    line[b][a] = Direction.RIGHT
    line[b + 1][a] = Direction.LEFT


def getResult(i: int) -> int:
    for j in range(H):
        if line[i][j] == Direction.LEFT:
            i -= 1
        elif line[i][j] == Direction.RIGHT:
            i += 1

    return i


def getAnswer(ver: int, hor: int, depth: int) -> int:
    if all(map(lambda x: getResult(x) == x, range(N))):
        return 0

    if depth >= 3:
        return INF

    minCnt = INF
    for i in range(ver, N):
        for j in range(H):
            if i <= ver and j <= hor:
                continue
            if line[i][j] is not None:
                continue

            if i + 1 < N and line[i + 1][j] is None:
                line[i][j] = Direction.RIGHT
                line[i + 1][j] = Direction.LEFT
                minCnt = min(minCnt, getAnswer(i, j, depth + 1))
                line[i + 1][j] = None
                line[i][j] = None

    return minCnt + 1


ans = getAnswer(0, -1, 0)

print(ans if ans <= 3 else -1)
