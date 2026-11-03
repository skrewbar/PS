import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    n = int(input())

    ans = 0

    i = 1
    j = 1
    while i < n:
        ans = max(ans, (n - i) * i * 10 + i)

        i *= 10
        j += 1

    print(ans)


main()
