import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

N, M = map(int, input().split())

campus = []
for i in range(N):
    campus.append(list(input()))

graph = {}
start = ()
for x in range(N):
    for y in range(M):
        if campus[x][y] == "I":
            start = (x, y)

        nxt_list = []

        if (x > 0) and (campus[x - 1][y] != "X"):
            nxt_list.append((x - 1, y))

        if (x + 1 < N) and (campus[x + 1][y] != "X"):
            nxt_list.append((x + 1, y))

        if (y > 0) and (campus[x][y - 1] != "X"):
            nxt_list.append((x, y - 1))

        if (y + 1 < M) and (campus[x][y + 1] != "X"):
            nxt_list.append((x, y + 1))

        graph[(x, y)] = list(nxt_list)


def bfs(graph: dict, start: tuple):
    people = 0
    visited = {i: False for i in graph.keys()}
    queue = deque([start])
    visited[start] = True
    while len(queue) > 0:
        current = queue.popleft()
        for nxt in graph[current]:
            if not visited[nxt]:
                x, y = nxt
                if campus[x][y] == "P":
                    people += 1
                queue.append(nxt)
                visited[nxt] = True
    return people


answer = bfs(graph, start)
if answer == 0:
    print("TT")
else:
    print(answer)
