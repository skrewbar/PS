import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    T, X = map(int, input().split())
    A = list(map(int, input().split()))

    v = -X
    for i in range(T + 1):
        if abs(A[i] - v) >= X:
            v = A[i]
            print(i, v)


main()
