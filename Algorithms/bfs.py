from collections import deque


def bfs(graph: dict, start: int):
    visited = {i: False for i in graph.keys()}
    queue = deque([start])
    visited[start] = True
    while len(queue) > 0:
        current = queue.popleft()
        for nxt in graph[current]:
            if not visited[nxt]:
                # nxt 방문
                queue.append(nxt)
                visited[nxt] = True
