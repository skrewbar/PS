import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    for i in range(N):
        if A[B[i] - 1] != i + 1:
            print("No")
            return

    print("Yes")


main()

