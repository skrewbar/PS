import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, K = map(int, input().split())
    A = sorted(map(int, input().split()), reverse=True)

    print(A[0] * ((K + 1) // 2) + A[1] * (K // 2))



main()
