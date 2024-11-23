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
byeol_dist = [float("inf") for _ in range(n + 1)]
byeol_dist[c] = 0
prev = [[] for _ in range(n + 1)]
queue = deque([c])
while queue:
    cur = queue.popleft()

    for next_, _ in connected_woods[cur]:
        if byeol_dist[next_] == byeol_dist[cur] + 1:
            prev[next_].append(cur)
        if byeol_dist[next_] != float("inf"):
            continue
        byeol_dist[next_] = byeol_dist[cur] + 1
        prev[next_].append(cur)
        queue.append(next_)
 
ans = b
hanbyeol = b
while hanbyeol != c:
    hanbyeol = min(
        prev[hanbyeol], key=lambda w: (byeol_dist[w], -len(connected_woods[w]), -w)
    )
    ans = min(hanbyeol, ans, key=lambda w: (toca_dist[w], w))
print(ans)
