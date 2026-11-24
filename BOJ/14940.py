import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


n, m = map(int, input().split())
map_ = []
for _ in range(n):
    map_.append(list(map(int, input().split())))


distance = [[-1 for _ in range(m)] for _ in range(n)]
for i in range(n):
    for j in range(m):
        if map_[i][j] == 0:
            distance[i][j] = 0


def bfs(x: int, y: int) -> None:
    q = deque([(x, y)])
    distance[x][y] = 0
    while q:
        x, y = q.popleft()

        if 0 < x and distance[x - 1][y] == -1:
            q.append((x - 1, y))
            distance[x - 1][y] = distance[x][y] + 1
        if 0 < y and distance[x][y - 1] == -1:
            q.append((x, y - 1))
            distance[x][y - 1] = distance[x][y] + 1
        if x < n - 1 and distance[x + 1][y] == -1:
            q.append((x + 1, y))
            distance[x + 1][y] = distance[x][y] + 1
        if y < m - 1 and distance[x][y + 1] == -1:
            q.append((x, y + 1))
            distance[x][y + 1] = distance[x][y] + 1


for i in range(n):
    for j in range(m):
        if map_[i][j] == 2:
            bfs(i, j)
            break

for i in range(n):
    print(*distance[i])
