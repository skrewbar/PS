def main():
    N, M, K = map(int, input().split())
    G, Y = zip(*(map(int, input().split()) for _ in range(K)))
    G = list(G)
    Y = list(Y)

    L = int(input())
    X = set(int(input()) for _ in range(L))

    dp = [[False] * N for _ in range(K)]
    dp[0][(M + G[0]) % N] = True
    dp[0][(M + Y[0]) % N] = True

    for i in range(1, K):
        for j in range(N):
            if j in X:
                continue

            if dp[i - 1][j]:
                dp[i][(j + G[i]) % N] = True
                dp[i][(j + Y[i]) % N] = True

    print("utopia" if dp[-1][0] else "dystopia")


main()
