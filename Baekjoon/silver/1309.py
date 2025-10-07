def solve():
    MOD = 9901

    N = int(input())

    cases = [[0, 0] for _ in range(N + 1)]
    # cases[i][0]: i번째 행에 사자가 없는 경우
    # cases[i][1]: i번째 행에 사자가 있는 경우
    cases[0][0] = 1

    for i in range(1, N + 1):
        cases[i][0] = cases[i - 1][0] + cases[i - 1][1]
        cases[i][1] = (cases[i - 1][0] << 1) + cases[i - 1][1]

        cases[i][0] %= MOD
        cases[i][1] %= MOD

    print((cases[N][0] + cases[N][1]) % MOD)


solve()
