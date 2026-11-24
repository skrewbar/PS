from collections import deque
import sys

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())

map_ = [list(map(int, list(input()))) for i in range(n)]

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]


def bfs():
    q = deque([(0, 0, False)])  # x, y, hasBroken
    distance = [[[float("inf"), float("inf")] for i in range(m)] for j in range(n)]
    distance[0][0][False] = 1

    while len(q) > 0:
        x, y, hasBroken = q.popleft()

        if x == n - 1 and y == m - 1:
            return distance[x][y][hasBroken]

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]

            if (
                (0 <= nx < n)
                and (0 <= ny < m)
                and (distance[nx][ny][hasBroken] == float("inf"))
            ):
                if map_[nx][ny] != 1:
                    q.append((nx, ny, hasBroken))
                    distance[nx][ny][hasBroken] = distance[x][y][hasBroken] + 1
                if not hasBroken:
                    q.append((nx, ny, True))
                    distance[nx][ny][True] = distance[x][y][hasBroken] + 1

    return -1


print(bfs())
