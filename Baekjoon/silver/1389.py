import sys

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())
graph = {i: set() for i in range(1, n + 1)}
dist = [[float("inf") for _ in range(n + 1)] for _ in range(n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    graph[a].add(b)
    graph[b].add(a)


for i in range(1, n + 1):
    dist[i][i] = 0
    for next in graph[i]:
        dist[i][next] = 1


for k in range(1, n + 1):
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

bacon = [0 for _ in range(n+1)]
bacon[0] = float("inf")
for i in range(1, n+1):
    for j in range(1, n+1):
        bacon[i] += dist[i][j]

print(bacon.index(min(bacon)))