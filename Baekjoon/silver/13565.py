import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


M, N = map(int, input().split())

fiber = []
for _ in range(M):
    fiber.append(list(input()))


start = []
graph = {}

for x in range(M):
    for y in range(N):
        current = (x, y)
        if (x == 0) and (fiber[x][y] == "0"):
            start.append(current)
        
        graph[current] = []

        if x > 0 and fiber[x-1][y] == "0":
            graph[current].append((x-1, y))
        if y > 0 and fiber[x][y-1] == "0":
            graph[current].append((x, y-1))
        if x < M-1 and fiber[x+1][y] == "0":
            graph[current].append((x+1, y))
        if y < N-1 and fiber[x][y+1] == "0":
            graph[current].append((x, y+1))


def bfs(graph:dict, start:list[tuple]) -> bool:
    visited = {i:False for i in graph.keys()}
    queue = deque(start)

    for s in start:
        visited[s] = True
    
    while len(queue) > 0:
        current = queue.popleft()
        for nxt in graph[current]:
            if not visited[nxt]:
                if nxt[0] == M - 1:
                    return True
                
                visited[nxt] = True
                queue.append(nxt)

    return False

if bfs(graph, start):
    print("YES")
else:
    print("NO")