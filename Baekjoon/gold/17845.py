import sys

input = lambda: sys.stdin.readline().rstrip()


n, k = map(int, input().split())
importance = [0]
time = [0]
dp = [[0 for _ in range(n + 1)] for _ in range(k + 1)]

for _ in range(k):
    i, t = map(int, input().split())
    importance.append(i)
    time.append(t)


for i in range(1, k + 1):
    for j in range(n + 1):
        dp[i][j] = dp[i - 1][j]

        if 0 <= j - time[i]:
            dp[i][j] = max(dp[i][j], dp[i - 1][j - time[i]] + importance[i])

print(dp[k][n])