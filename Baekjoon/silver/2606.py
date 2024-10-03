import sys
from collections import deque


graph = {i: set() for i in range(1, int(input()) + 1)}

for _ in range(int(input())):
    c1, c2 = map(int, input().split())

    graph[c1].add(c2)
    graph[c2].add(c1)


def bfs(graph: dict, start: int) -> int:
    infected = 0
    visited = {i: False for i in graph.keys()}
    queue = deque([start])
    visited[start] = True

    while len(queue) > 0:
        current = queue.popleft()
        for nxt in graph[current]:
            if not visited[nxt]:
                infected += 1
                queue.append(nxt)
                visited[nxt] = True

    return infected


print(bfs(graph, 1))
