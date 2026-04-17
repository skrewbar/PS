import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    a.sort(reverse=True)

    for i in range(1, n):
        if a[i] == a[i - 1]:
            print(-1)
            return

    print(*a)


def main():
    t = int(input())
    for _ in range(t):
        solve()


main()
