import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

for t in range(int(input())):
    n, k = map(int, input().split())
    ownBuildTime = [0] + list(map(int, input().split()))
    totalbuildTime = [0 for _ in range(n + 1)]
    next = [[] for _ in range(n + 1)]
    indegree = [0 for _ in range(n + 1)]

    for _ in range(k):
        a, b = map(int, input().split())
        next[a].append(b)
        indegree[b] += 1

    w = int(input())

    queue = deque()
    for i in range(1, n + 1):
        if indegree[i] == 0:
            queue.append(i)
            totalbuildTime[i] = ownBuildTime[i]

    while queue:
        n = queue.popleft()
        if n == w:
            break
        for nxt in next[n]:
            totalbuildTime[nxt] = max(
                totalbuildTime[nxt], totalbuildTime[n] + ownBuildTime[nxt]
            )
            indegree[nxt] -= 1
            if indegree[nxt] == 0:
                queue.append(nxt)

    print(totalbuildTime[w])
