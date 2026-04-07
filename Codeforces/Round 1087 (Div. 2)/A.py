def solve():
    n, c, k = map(int, input().split())
    a = sorted(map(int, input().split()))

    for i in range(n):
        if a[i] > c:
            break

        delta = min(k, c - a[i])
        c += a[i] + delta
        k -= delta

    print(c)


def main():
    for _ in range(int(input())):
        solve()


main()
