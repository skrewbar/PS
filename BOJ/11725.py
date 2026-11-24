from collections import deque

nodeNumber = int(input())

line = {i: [] for i in range(nodeNumber + 1)}

for i in range(nodeNumber - 1):
    a, b = map(int, input().split())
    line[a].append(b)
    line[b].append(a)

parent = [i for i in range(nodeNumber + 1)]


def bfs(start: int):
    queue = deque([start])
    visited = {i: False for i in range(1, nodeNumber + 1)}
    while queue:
        cur = queue.popleft()
        for next in line[cur]:
            if not visited[next]:
                parent[next] = cur
                visited[next] = True
                queue.append(next)


bfs(1)

for i in range(2, nodeNumber + 1):
    print(parent[i])
