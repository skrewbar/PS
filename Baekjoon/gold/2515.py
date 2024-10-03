import sys

input = lambda: sys.stdin.readline().rstrip()


n, s = map(int, input().split())
paints = [(0, 0)] + [tuple(map(int, input().split())) for _ in range(n)]
paints.sort()
limit = [0] * (n + 1)
dp = [0] * (n + 1)

for i in range(1, n + 1):
    limit[i] = limit[i - 1] + 1
    while limit[i] < i:
        if paints[i][0] - paints[limit[i]][0] < s:
            break
        limit[i] += 1
    limit[i] -= 1

for i in range(1, n + 1):
    dp[i] = dp[limit[i]] + paints[i][1]
    dp[i] = max(dp[i], dp[i - 1])

print(dp[n])
