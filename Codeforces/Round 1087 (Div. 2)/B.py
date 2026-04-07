def solve():
    n = int(input())
    a = list(map(int, input().split()))

    for i in range(n):
        g = 0
        l = 0
        for j in range(i + 1, n):
            if a[i] < a[j]:
                g += 1
            elif a[i] > a[j]:
                l += 1

        print(max(g, l), end=" ")

    print()


def main():
    for _ in range(int(input())):
        solve()


main()
