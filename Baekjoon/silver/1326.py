from collections import deque

n = int(input())
stones = [None] + list(map(int, input().split()))
departure, arrival = map(int, input().split())

adj = [[] for _ in range(n + 1)]
for i in range(1, n + 1):
    for j in range(1, n + 1):
        if i != j and abs(j - i) % stones[i] == 0:
            adj[i].append(j)

count = [None for _ in range(n + 1)]
count[departure] = 0
queue = deque([departure])
while queue:
    now = queue.popleft()
    if now == arrival:
        break

    for next_ in adj[now]:
        if count[next_] is not None:
            continue
        count[next_] = count[now] + 1
        queue.append(next_)

print(count[arrival] if count[arrival] is not None else -1)
