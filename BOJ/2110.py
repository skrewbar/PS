def main():
    N, C = map(int, input().split())
    x = sorted([int(input()) for _ in range(N)])

    def possible(min_dist: int) -> bool:
        cnt = 1
        last = 0

        for i in range(1, N):
            if x[i] - x[last] < min_dist:
                continue
            last = i
            cnt += 1

        return cnt >= C

    lo = 0
    hi = x[-1] - x[0] + 1
    while lo < hi:
        mid = (lo + hi) // 2

        if possible(mid):
            lo = mid + 1
        else:
            hi = mid

    print(lo - 1)


main()
