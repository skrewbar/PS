import sys

input = lambda: sys.stdin.readline().rstrip()


def delta(c):
    if c == "L":
        return -1
    if c == "R":
        return 1
    return 0


def main():
    T, X, Y = map(int, input().split())
    A = input()
    B = input()

    ans = 0

    for i in range(T):
        X += delta(A[i])
        Y += delta(B[i])

        if X == Y:
            ans += 1

    print(ans)


main()
