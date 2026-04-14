def main():
    N = int(input())
    k = int(input())

    def get_le_count(n: int) -> int:
        ret = 0

        for i in range(1, N + 1):
            ret += min(n // i, N)

        return ret

    lo = 0
    hi = N * N + 1
    while lo < hi:
        mid = (lo + hi) // 2

        if get_le_count(mid) >= k:
            hi = mid
        else:
            lo = mid + 1

    print(lo)


main()
