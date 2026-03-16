import sys

sys.setrecursionlimit(10**6)

input = lambda: sys.stdin.readline().rstrip()


def solve():
    # input
    V, E = map(int, input().split())
    adj = [[] for _ in range(V + 1)]

    for _ in range(E):
        u, v = map(int, input().split())
        adj[u].append(v)
        adj[v].append(u)

    # determine whether the graph is bipartite
    def is_bipartite() -> bool:
        color = [-1] * (V + 1)
        # the colors of adjacent vertices must be different

        ret = True

        def dfs(cur: int) -> None:
            nonlocal ret

            for nxt in adj[cur]:
                if color[nxt] != -1:
                    if color[nxt] == color[cur]:
                        ret = False
                    continue

                color[nxt] = color[cur] ^ 1
                dfs(nxt)

        for i in range(1, V + 1):
            if color[i] != -1:
                continue
            color[i] = 0
            dfs(i)

        return ret

    print("YES" if is_bipartite() else "NO")


def main():
    K = int(input())
    for _ in range(K):
        solve()


main()
