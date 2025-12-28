def main():
    n, k = map(int, input().split())

    choice = [[1] * n for _ in range(n)]
    for i in range(1, n):
        for j in range(1, i):
            choice[i][j] = choice[i - 1][j - 1] + choice[i - 1][j]

    print(choice[n - 1][k - 1])


main()
