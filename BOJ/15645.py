def main():
    INF = int(1e9)

    N = int(input())

    table = [list(map(int, input().split())) for _ in range(N)]

    minScore = [[INF] * 3 for _ in range(N)]
    maxScore = [[0] * 3 for _ in range(N)]

    minScore[0] = list(table[0])
    maxScore[0] = list(table[0])

    for i in range(1, N):
        for j in range(3):
            for k in range(j - 1, j + 2):
                if k < 0 or k >= 3:
                    continue
                minScore[i][j] = min(minScore[i][j], minScore[i - 1][k] + table[i][j])
                maxScore[i][j] = max(maxScore[i][j], maxScore[i - 1][k] + table[i][j])

    print(max(maxScore[-1]), min(minScore[-1]))


main()
