import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    n, c = map(int, input().split())
    a = sorted(map(int, input().split()), reverse=True)

    big = 0
    while big < n and a[big] > c:
        big += 1

    ans = big
    mul = 1
    for i in range(big, n):
        if a[i] * mul > c:
            ans += 1
            continue
        mul *= 2

    print(ans)


def main():
    t = int(input())
    for _ in range(t):
        solve()


main()

