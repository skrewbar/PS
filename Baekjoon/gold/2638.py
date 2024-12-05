from collections import deque

n, m = map(int, input().split())

cheese = [list(map(int, input().split())) for _ in range(n)]


def get_melt_list(cheese: list[list[int]]) -> list[tuple[int, int]]:
    visited = [[0] * m for _ in range(n)]
    queue = deque(((0, 0),))
    melt_list = []
    while queue:
        x, y = queue.popleft()

        for k in range(4):
            nx = x + [0, 0, 1, -1][k]
            ny = y + [1, -1, 0, 0][k]

            if 0 <= nx < n and 0 <= ny < m:
                if cheese[nx][ny] == 0 and not visited[nx][ny]:
                    queue.append((nx, ny))

                visited[nx][ny] += 1
                if cheese[nx][ny] == 1 and 2 <= visited[nx][ny]:
                    melt_list.append((nx, ny))
    return melt_list


hour = 0
while True:
    melt_list = get_melt_list(cheese)
    if not melt_list:
        break
    for x, y in melt_list:
        cheese[x][y] = 0
    hour += 1

print(hour)
