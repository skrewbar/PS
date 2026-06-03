import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, M = map(int, input().split())

    cnt = [0] * (N + 1)

    for _ in range(M):
        a, b = map(int, input().split())
        cnt[a] += 1
        cnt[b] += 1

    for i in range(1, N + 1):
        if cnt[i] % 2 == 1:
            print("NO")
            return

    print("YES")


main()
