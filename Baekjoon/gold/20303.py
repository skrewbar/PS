from collections import deque

n, m, k = map(int, input().split())
candy = list(map(int, input().split()))

adj = [[] for _ in range(n)]
for _ in range(m):
    a, b = map(lambda x: int(x) - 1, input().split())
    adj[a].append(b)
    adj[b].append(a)


candy_group = []
head_count = []
stolen = [False for _ in range(n)]
for i in range(n):
    if not stolen[i]:
        stolen[i] = True
        sum_ = candy[i]
        head = 1
        queue = deque()
        queue.append(i)
        while queue:
            cur = queue.popleft()
            for next_ in adj[cur]:
                if stolen[next_]:
                    continue
                stolen[next_] = True
                sum_ += candy[next_]
                head += 1
                queue.append(next_)
        candy_group.append(sum_)
        head_count.append(head)


dp = [[0] * k for _ in range(n)]
for i in range(len(candy_group)):
    for j in range(k):
        dp[i][j] = dp[i - 1][j]

        head = j - head_count[i]
        if head < 0:
            continue
        dp[i][j] = max(candy_group[i] + dp[i - 1][head], dp[i][j])

print(dp[len(candy_group) - 1][k - 1])
