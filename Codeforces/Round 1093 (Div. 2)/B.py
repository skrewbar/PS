import sys

input = lambda: sys.stdin.readline().rstrip()


def solve():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))

    consec = 1
    for i in range(1, n):
        if a[i] == a[i - 1]:
            consec += 1
        else:
            consec = 1

        if consec >= m:
            print("NO")
            return

    print("YES")


def main():
    t = int(input())
    for _ in range(t):
        solve()


main()
