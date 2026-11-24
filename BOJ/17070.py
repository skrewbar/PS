HORIZONTAL = 0
VERTICAL = 1
DIAGONAL = 2

n = int(input())
house = [list(map(int, input().split())) for _ in range(n)]
dp = [[[0] * 3 for _ in range(n)] for _ in range(n)]

dp[0][1][HORIZONTAL] = 1


for i in range(n):
    for j in range(n):
        if 0 < j and house[i][j - 1] + house[i][j] == 0:  # 가로
            if j < n - 1 and house[i][j + 1] == 0:
                dp[i][j + 1][HORIZONTAL] += dp[i][j][HORIZONTAL]
            if (
                i < n - 1
                and j < n - 1
                and house[i][j + 1] + house[i + 1][j] + house[i + 1][j + 1] == 0
            ):
                dp[i + 1][j + 1][DIAGONAL] += dp[i][j][HORIZONTAL]

        if 0 < i and house[i][j] + house[i - 1][j] == 0:  # 세로
            if i < n - 1 and house[i + 1][j] == 0:
                dp[i + 1][j][VERTICAL] += dp[i][j][VERTICAL]
            if (
                i < n - 1
                and j < n - 1
                and house[i][j + 1] + house[i + 1][j] + house[i + 1][j + 1] == 0
            ):
                dp[i + 1][j + 1][DIAGONAL] += dp[i][j][VERTICAL]

        if (
            0 < i
            and 0 < j
            and house[i - 1][j - 1] + house[i - 1][j] + house[i][j - 1] + house[i][j]
            == 0
        ):
            if j < n - 1 and house[i][j + 1] == 0:
                dp[i][j + 1][HORIZONTAL] += dp[i][j][DIAGONAL]
            if i < n - 1 and house[i + 1][j] == 0:
                dp[i + 1][j][VERTICAL] += dp[i][j][DIAGONAL]
            if (
                i < n - 1
                and j < n - 1
                and house[i][j + 1] + house[i + 1][j] + house[i + 1][j + 1] == 0
            ):
                dp[i + 1][j + 1][DIAGONAL] += dp[i][j][DIAGONAL]

print(sum(dp[n - 1][n - 1]))
