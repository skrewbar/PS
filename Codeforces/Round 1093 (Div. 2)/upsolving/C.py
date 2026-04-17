import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    p, q = map(int, input().split())

    t = p + 2 * q

    hi = int((-1 + (1 + 2 * t) ** (1 / 2)) / 2) + 200

    for n in range(1, hi):
        numer = t - n
        denom = 2 * n + 1

        if numer % denom != 0 or numer == 0:
            continue

        m = numer // denom

        if abs(n - m) > p:
            continue

        print(n, m)
        return

    print(-1)


def main():
    t = int(input())
    for _ in range(t):
        solve()


main()
