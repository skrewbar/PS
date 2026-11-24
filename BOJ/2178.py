N, M = map(int, input().split())
maze = []
for i in range(N):
    maze.append(list(map(int, list(input()))))

graph = {}
for x in range(N):
    for y in range(M):
        if maze[x][y] == 1:
            nxt_list = []

            if (0 <= x - 1) and (maze[x - 1][y] == 1):
                nxt_list.append((x - 1, y))
            if (x + 1 <= N - 1) and (maze[x + 1][y] == 1):
                nxt_list.append((x + 1, y))
            if (0 <= y - 1) and (maze[x][y - 1] == 1):
                nxt_list.append((x, y - 1))
            if (y + 1 <= M - 1) and (maze[x][y + 1] == 1):
                nxt_list.append((x, y + 1))

            graph[(x, y)] = nxt_list


def bfs(graph: dict, start: tuple):
    visited = {i: False for i in graph.keys()}
    queue = [start]
    visited[start] = True
    while len(queue) > 0:
        current = queue.pop(0)
        for nxt in graph[current]:
            if not visited[nxt]:
                # nxt 방문
                Xc, Yc = current[0], current[1]
                Xn, Yn = nxt[0], nxt[1]
                maze[Xn][Yn] = maze[Xc][Yc] + 1

                if nxt == (N - 1, M - 1):
                    return maze[Xn][Yn]

                queue.append(nxt)
                visited[nxt] = True


print(bfs(graph, (0, 0)))

