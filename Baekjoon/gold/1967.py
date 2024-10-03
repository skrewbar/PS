import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

n = int(input())
graph = {i: [] for i in range(1, n + 1)}

for i in range(n - 1):
    node1, node2, value = map(int, input().split())
    graph[node1].append((node2, value))
    graph[node2].append((node1, value))


distance = [-1 for i in range(n + 1)]


def bfs(start) -> int:
    queue = deque([start])
    distance[start] = 0

    while queue:
        node = queue.popleft()
        for next, value in graph[node]:
            if distance[next] == -1:
                queue.append(next)
                distance[next] = distance[node] + value
    return


bfs(1)
furthestNode = distance.index(max(distance))
distance = [-1 for i in range(n + 1)]
bfs(furthestNode)
print(max(distance))
