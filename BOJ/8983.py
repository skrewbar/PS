from typing import NamedTuple


class Point(NamedTuple):
    x: int
    y: int


def main():
    M, N, L = map(int, input().split())

    ranges = sorted(map(int, input().split()))
    animals = [Point(*map(int, input().split())) for _ in range(N)]

    ans = 0
    for animal in animals:
        lo = 0
        hi = M
        while lo < hi:
            mid = (lo + hi) // 2

            if ranges[mid] < animal.x:
                lo = mid + 1
            else:
                hi = mid

        if lo < M and abs(ranges[lo] - animal.x) + animal.y <= L:
            ans += 1
        elif lo - 1 >= 0 and abs(ranges[lo - 1] - animal.x) + animal.y <= L:
            ans += 1

    print(ans)


main()
