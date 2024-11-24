import sys
from heapq import *
from collections import deque

n, m = map(int, input().split())
a, b, c = map(int, input().split())

connected_woods = [[] for _ in range(n + 1)]
for _ in range(m):
    i, j, k = map(int, input().split())
    connected_woods[i].append((j, k))
    connected_woods[j].append((i, k))

for i in range(1, n + 1):
    connected_woods[i].sort(key=lambda e: (-len(connected_woods[e[0]]), -e[0]))

# toca
toca_dist = [float("inf") for _ in range(n + 1)]
toca_dist[a] = 0
queue = [(0, a)]
while queue:
    cur_dist, cur = heappop(queue)
    if toca_dist[cur] < cur_dist:
        continue
    for next_, edge_dist in connected_woods[cur]:
        next_dist = cur_dist + edge_dist
        if next_dist < toca_dist[next_]:
            toca_dist[next_] = next_dist
            heappush(queue, (next_dist, next_))

# hanbyeol
visited = [False for _ in range(n + 1)]
visited[b] = True
prev = [None for _ in range(n + 1)]
queue = deque([b])
while queue:
    cur = queue.popleft()

    for next_, _ in connected_woods[cur]:
        if visited[next_]:
            continue
        visited[next_] = True
        prev[next_] = cur
        queue.append(next_)

ans = c
hanbyeol = c
while hanbyeol != b:
    hanbyeol = prev[hanbyeol]
    ans = min(hanbyeol, ans, key=lambda w: (toca_dist[w], w))
print(ans)
