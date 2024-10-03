import sys

sys.setrecursionlimit(10**6)

input = lambda: sys.stdin.readline().rstrip()

t = int(input())


def deleteNearCabbage(x: int, y: int, m: int, n: int, ground: list[list[int]]) -> None:
    if ground[x][y] == 0:
        return

    ground[x][y] = 0
    if 0 < x:
        deleteNearCabbage(x - 1, y, m, n, ground)
    if x < m - 1:
        deleteNearCabbage(x + 1, y, m, n, ground)
    if 0 < y:
        deleteNearCabbage(x, y - 1, m, n, ground)
    if y < n - 1:
        deleteNearCabbage(x, y + 1, m, n, ground)


for case in range(t):
    wormCount = 0
    m, n, k = map(int, input().split())
    ground = [[0 for i in range(n)] for j in range(m)]

    for i in range(k):
        x, y = map(int, input().split())
        ground[x][y] = 1

    for x in range(m):
        for y in range(n):
            if ground[x][y] == 1:
                wormCount += 1
                deleteNearCabbage(x, y, m, n, ground)

    print(wormCount)
