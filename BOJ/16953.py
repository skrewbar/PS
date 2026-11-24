import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


a, b = map(int, input().split())
count = {}

queue = deque([a])
count[a] = 0

found = False
while queue:
    now = queue.popleft()

    if now == b:
        found = True
        break

    if now > b:
        continue

    if not (now * 2 in count):
        count[now * 2] = count[now] + 1
        queue.append(now * 2)

    if not (now * 10 + 1 in count):
        count[now * 10 + 1] = count[now] + 1
        queue.append(now * 10 + 1)

print(count[b] + 1) if found else print(-1)
