import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())
map_ = [list(map(int, list(input()))) for _ in range(n)]

dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]


def bfs(start: tuple[int, int], number: int) -> int:
    count = 1
    queue = deque([start])
    map_[start[0]][start[1]] = number
    while queue:
        x, y = queue.popleft()

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]

            if (0 <= nx < n) and (0 <= ny < m) and (map_[nx][ny] == 0):
                queue.append((nx, ny))
                map_[nx][ny] = number
                count += 1
    return count


number = 2
numberMap = {}
for i in range(n):
    for j in range(m):
        if map_[i][j] == 0:
            numberMap[number] = bfs((i, j), number)
            number += 1

for i in range(n):
    for j in range(m):
        if map_[i][j] == 1:
            visited = set()
            for k in range(4):
                ni = i + dx[k]
                nj = j + dy[k]

                if (0 <= ni < n) and (0 <= nj < m) and (map_[ni][nj] != 1):
                    visited.add(map_[ni][nj])

            ans = 1
            for a in visited:
                ans += numberMap[a]

            print(ans % 10, end="")
        else:
            print(0, end="")
    print()
