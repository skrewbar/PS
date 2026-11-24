from heapq import *

n, m = map(int, input().split())

indegree = [0 for _ in range(n + 1)]
adj = [[] for _ in range(n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    adj[a].append(b)
    indegree[b] += 1

queue: list[int] = []
for i in range(1, n + 1):
    if indegree[i] == 0:
        heappush(queue, i)

while queue:
    print(cur := heappop(queue), end=" ")

    for next_ in adj[cur]:
        indegree[next_] -= 1
        if indegree[next_] == 0:
            heappush(queue, next_)
