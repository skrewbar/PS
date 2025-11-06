from dataclasses import dataclass
from bisect import bisect_left, bisect_right
from typing import Callable


@dataclass(order=True)
class Food:
    spiciness: int
    sweetness: int


def main():
    N, Q = map(int, input().split())

    foods: list[Food] = []
    for _ in range(N):
        foods.append(Food(*map(int, input().split())))
    foods.sort()

    for _ in range(Q):
        u, v, x, y = map(int, input().split())

        key: Callable[[Food], int] = lambda x: x.spiciness
        lo = bisect_left(foods, u, key=key)
        hi = bisect_right(foods, v, key=key)

        ans = 0
        for i in range(lo, hi):
            if x <= foods[i].sweetness <= y:
                ans += 1

        print(ans)


main()
