import sys

input = lambda: sys.stdin.readline().rstrip()

MOD = 998244353


fac = [1] * 404040
for i in range(2, len(fac)):
    fac[i] = fac[i - 1] * i % MOD


def nHr(n: int, r: int):
    if n == 0:
        return 0

    return fac[n + r - 1] * pow(fac[n - 1], MOD - 2, MOD) * pow(fac[r], MOD - 2, MOD)


def main():
    N, K = map(int, input().split())
    A = list(map(int, input().split()))

    a_set = set(A)

    stucks = []
    i = 0
    for _ in range(K + 1):
        while i in a_set:
            i += 1
        stucks.append(i)
        i += 1

    ans = 0

    for i in range(K + 1):
        ans += nHr(stucks[i], K - i)
        ans %= MOD

    print(ans)


main()
