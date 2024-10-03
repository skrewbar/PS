n = int(input())
arr = [-float("inf")] + list(map(int, input().split()))
dp = [[-float("inf") for _ in range(2)] for _ in range(n + 1)]

dp[1][False] = max(arr[1], 0)
for i in range(2, n + 1):
    dp[i][False] = max(dp[i - 1][False] + arr[i], arr[i], 0)
    dp[i][True] = max(
        dp[i - 1][True] + arr[i], dp[i - 2][False] + arr[i], arr[i - 2] + arr[i], 0
    )

ans = -float("inf")

for i in range(1, n + 1):
    for j in range(2):
        ans = max(ans, dp[i][j])

if ans == 0:
    ans = max(arr)

print(ans)