import sys

input = lambda: sys.stdin.readline().rstrip()

MOD = 998244353


def main():
    N = int(input())

    M = [0] * N
    a = [0] * N

    for i in range(N):
        M_i, a_i = map(int, input().split())
        M[i] = M_i
        a[i] = a_i
    inv = pow(sum(a), -1, MOD)

    dp = [-1] * pow(11, N)
    pow11 = [0] * (N + 1)
    pow11[0] = 1
    for i in range(1, N + 1):
        pow11[i] = pow11[i - 1] * 11
        
    dp = [-1] * pow11[N]
    last = 0
    for i in range(N):
        last += pow11[i] * M[i]
    dp[last] = 0

    def get_dp(num: int = 0) -> int:
        if dp[num] != -1:
            return dp[num]

        prob = 0
        a_sum = 0
        for i in range(N):
            if num % pow11[i + 1] // pow11[i] == M[i]:
                continue

            prob += a[i] * inv
            a_sum += a[i]

        ex = pow(prob, -1, MOD)
        sum_inv = pow(a_sum, -1, MOD)

        for i in range(N):
            if num % pow11[i + 1] // pow11[i] == M[i]:
                continue

            ex += get_dp(num + pow11[i]) * a[i] * sum_inv
            ex %= MOD

        dp[num] = ex
        return ex

    print(get_dp())


main()
