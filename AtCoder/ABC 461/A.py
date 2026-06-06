import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    A, D = map(int, input().split())
    print("Yes" if A <= D else "No")


main()

