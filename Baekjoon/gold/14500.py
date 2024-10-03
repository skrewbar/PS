import sys

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())

p = [list(map(int, input().split())) for _ in range(n)]
visited = [[False for _ in range(m)] for _ in range(n)]
# 'p'aper

ans = 0

dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]


def dfs(x: int, y: int, depth: int) -> int:
    if depth == 4:
        return p[x][y]

    ret = 0

    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]

        if (0 <= nx and nx < n) and (0 <= ny and ny < m):
            if visited[nx][ny]:
                continue

            visited[nx][ny] = True
            ret = max(ret, dfs(nx, ny, depth + 1))
            visited[nx][ny] = False

    return ret + p[x][y]


for i in range(n):
    for j in range(m):
        visited[i][j] = True
        ans = max(ans, dfs(i, j, 1))
        visited[i][j] = False

        if i + 1 < n and j + 2 < m:
            ans = max(ans, p[i][j] + p[i][j + 1] + p[i][j + 2] + p[i + 1][j + 1])
        if 0 <= i - 2 and 0 <= j - 1:
            ans = max(ans, p[i][j] + p[i - 1][j] + p[i - 2][j] + p[i - 1][j - 1])
        if 0 <= i - 1 and 0 <= j - 2:
            ans = max(ans, p[i][j] + p[i][j - 1] + p[i][j - 2] + p[i - 1][j - 1])
        if i + 2 < n and j + 1 < m:
            ans = max(ans, p[i][j] + p[i + 1][j] + p[i + 2][j] + p[i + 1][j + 1])

print(ans)
