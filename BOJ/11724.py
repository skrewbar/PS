import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

N, M = map(int, input().split())
nodes = {i for i in range(1, N + 1)}
graph = {}

for i in range(M):
    u, v = map(int, input().split())

    if u in graph:
        graph[u].add(v)
    else:
        graph[u] = {v}
    graph[u].add(u)

    if v in graph:
        graph[v].add(u)
    else:
        graph[v] = {u}
    graph[v].add(v)


def bfs(graph: dict, start: int) -> None:
    visited = {i: False for i in graph.keys()}
    queue = deque([start])
    visited[start] = True
    while len(queue) > 0:
        current = queue.popleft()
        if current in nodes:
            nodes.remove(current)
        for nxt in graph[current]:
            if not visited[nxt]:
                if nxt in nodes:
                    nodes.remove(nxt)

                queue.append(nxt)
                visited[nxt] = True
            if current in graph:
                graph.pop(current)


answer = 0
while nodes:
    if len(graph) == 0:
        answer += len(nodes)
        break
    bfs(graph, list(graph.keys())[0])
    answer += 1
print(answer)
