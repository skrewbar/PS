import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, K = map(int, input().split())
    A = list(map(int, input().split()))

    def maxChange(limit):
        change = 0
        for i in range(1, limit):
            change += abs(A[i - 1] - A[i])

        ret = change

        for i in range(limit, N):
            change -= abs(A[i - limit] - A[i - limit + 1])
            change += abs(A[i - 1] - A[i])
            ret = max(ret, change)

        return ret

    lo = 1
    hi = N + 1

    while lo < hi:
        m = (lo + hi) // 2

        if maxChange(m) < K:
            lo = m + 1
        else:
            hi = m

    print(lo if lo <= N else -1)


main()
