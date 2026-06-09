import sys
from bisect import bisect_left, bisect_right

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, M, Q = map(int, input().split())
    B = sorted(map(int, input().split()))
    cnt = [0] * (M + 5)

    queries = [tuple(map(int, input().split())) for _ in range(Q)]
    queries.sort()

    for l, r in queries:
        lb = bisect_left(B, l)
        ub = bisect_right(B, r)

        cnt[lb] += 1
        cnt[ub] -= 1

    ans = 0
    for i in range(M):
        cnt[i] += cnt[i - 1]
        ans += cnt[i] & 1

    print(ans)


main()
