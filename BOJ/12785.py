MOD = int(1e6) + 7


def main():
    w, h = map(int, input().split())
    x, y = map(int, input().split())

    dp = [[0] * (w + 1) for _ in range(h + 1)]

    for i in range(1, h + 1):
        dp[i][1] = 1
        for j in range(2, w + 1):
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD

    print(dp[y][x] * dp[h - y + 1][w - x + 1] % MOD)


main()
