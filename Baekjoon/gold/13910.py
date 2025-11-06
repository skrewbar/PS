def main():
    N, M = map(int, input().split())
    S = list(map(int, input().split()))

    dp = [float("inf")] * (N + 1)
    dp[0] = 0
    for i in range(1, N + 1):
        for wok1 in range(M):
            if i - S[wok1] >= 0:
                dp[i] = min(dp[i], dp[i - S[wok1]] + 1)

            for wok2 in range(wok1 + 1, M):
                if i - S[wok1] - S[wok2] >= 0:
                    dp[i] = min(dp[i], dp[i - S[wok1] - S[wok2]] + 1)

    print(-1 if dp[N] == float("inf") else dp[N])


main()
