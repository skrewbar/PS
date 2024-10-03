from collections import deque

M, N = map(int, input().split())
tomatoes = []
for i in range(N):
    tomatoes.append(list(map(int, input().split())))

graph = {}
starts = []

for x in range(N):
    for y in range(M):
        if tomatoes[x][y] == 1:
            starts.append((x, y))

        nxt_list = []
        if (x > 0) and (tomatoes[x - 1][y] != -1):
            nxt_list.append((x - 1, y))

        if (x + 1 < N) and (tomatoes[x + 1][y] != -1):
            nxt_list.append((x + 1, y))

        if (y > 0) and (tomatoes[x][y - 1] != -1):
            nxt_list.append((x, y - 1))

        if (y + 1 < M) and (tomatoes[x][y + 1] != -1):
            nxt_list.append((x, y + 1))

        graph[(x, y)] = nxt_list


def bfs(graph: dict, starts: list) -> int:
    day = 0
    visited = {i: False for i in graph.keys()}
    q1 = deque(starts)
    q2 = deque()

    for node in q1:
        visited[node] = True

    while (len(q1) > 0) or (len(q2) > 0):
        if len(q1) == 0:
            q1, q2 = q2, q1
            day += 1
        current = q1.popleft()
        for nxt in graph[current]:
            if not visited[nxt]:
                x, y = nxt[0], nxt[1]
                tomatoes[x][y] = 1

                q2.append(nxt)
                visited[nxt] = True
    return day


day = bfs(graph, starts)

ripe = True
for x in range(N):
    for y in range(M):
        if tomatoes[x][y] == 0:
            ripe = False
            print(-1)
            break
    if not ripe:
        break

if ripe:
    print(day)
