import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())
indegree = [0 for _ in range(n + 1)]
nextList = [[] for _ in range(n + 1)]

for _ in range(m):
    p, s = map(int, input().split())
    nextList[p].append(s)
    indegree[s] += 1

queue = deque()
for i in range(1, n + 1):
    if indegree[i] == 0:
        queue.append(i)


while queue:
    curr = queue.popleft()
    print(curr, end=" ")

    for next in nextList[curr]:
        indegree[next] -= 1
        if indegree[next] == 0:
            queue.append(next)
