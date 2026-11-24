import sys

sys.setrecursionlimit(10**6)

input = lambda: sys.stdin.readline().rstrip()


MOD = int(1e9 + 7)


def solve():
    N = int(input())
    child_edges = [[] for _ in range(N)]

    def get_output(cur: int, mod: int):
        if not child_edges[cur]:
            return 1

        output = 0

        for child, weight in child_edges[cur]:
            output += get_output(child, mod) * weight % mod
            output %= mod

        return output

    a = [-1] + list(map(int, input().split()))
    w = [-1] + list(map(int, input().split()))

    for i in range(1, N):
        child_edges[a[i]].append((i, w[i]))

    if get_output(0, 2) == 0:
        print("FREAK OUT")
    else:
        print(get_output(0, MOD))


def main():
    T = int(input())

    for _ in range(T):
        solve()


main()
