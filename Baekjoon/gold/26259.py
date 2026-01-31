INF = int(2e9)


def main():
    N, M = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(N)]
    x1, y1, x2, y2 = map(int, input().split())

    if x1 > x2:
        x1, x2 = x2, x1
    if y1 > y2:
        y1, y2 = y2, y1

    def isRightOpen(x: int, y: int) -> bool:
        if y1 == y2 and y + 1 == y1 and x1 <= x < x2:
            return False
        return True

    def isDownOpen(x: int, y: int) -> bool:
        if x1 == x2 and x + 1 == x1 and y1 <= y < y2:
            return False
        return True

    dp = [[-INF] * M for _ in range(N)]

    dp[0][0] = a[0][0]

    for i in range(N):
        for j in range(M):
            if dp[i][j] == -INF:
                continue

            if i + 1 < N and isDownOpen(i, j):
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + a[i + 1][j])
            if j + 1 < M and isRightOpen(i, j):
                dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + a[i][j + 1])

    if dp[N - 1][M - 1] == -INF:
        print("Entity")
    else:
        print(dp[N - 1][M - 1])


main()
