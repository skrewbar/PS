def main():
    N, M = map(int, input().split())
    board = input()
    word = input()

    dp = [[0] * N for _ in range(M)]
    for j in range(N):
        if word[0] == board[j]:
            dp[0][j] = 1

    for i in range(1, M):
        for j in range(N):
            if j - 1 >= 0:
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1])
            if j + 1 < N:
                dp[i][j] = max(dp[i][j], dp[i - 1][j + 1])

            if word[i] == board[j]:
                dp[i][j] += 1

    print(max(dp[M - 1]))


main()
