import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N = int(input())
    L = list(map(int, input().split()))

    def dfs(i: int, p: int) -> int:
        if i == N:
            return 0

        ret = dfs(i + 1, p + L[i]) + (p < 0 and p + L[i] >= 0)
        ret = max(ret, dfs(i + 1, p - L[i]) + (p >= 0 and p - L[i] < 0))

        return ret

    print(dfs(0, 0))


main()
