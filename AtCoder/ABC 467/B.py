import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N = int(input())

    X = Y = 10000

    for _ in range(N):
        A, B, S = input().split()
        A = int(A)
        B = int(B)

        if S == "keep":
            X -= B
        else:
            X -= A
        Y -= A

    print(Y - X)


main()
