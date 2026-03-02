MOD = int(1e9) + 7


def main():
    N = int(input())
    S = input()

    is_sour = [[False] * N for _ in range(N)]
    for i in range(N - 1):
        if S[i] == ">" and S[i + 1] == "<":
            is_sour[i][i + 1] = True

    for len in range(2, N + 1, 2):
        for i in range(N - len + 1):
            j = i + len - 1

            if is_sour[i + 1][j - 1] and S[i] == ">" and S[j] == "<":
                is_sour[i][j] = True

    count = [[0] * N for _ in range(N)]
    count[0][N - 1] = 1
    for len in range(N, 2, -1):
        for i in range(N - len + 1):
            j = i + len - 1

            count[i + 1][j] = (count[i + 1][j] + count[i][j]) % MOD
            count[i][j - 1] = (count[i][j - 1] + count[i][j]) % MOD

    answer = 0
    for i in range(N):
        for j in range(i + 1, N, 2):
            if is_sour[i][j]:
                answer = (answer + count[i][j]) % MOD

    print(answer)


main()
