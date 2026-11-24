INF = int(1e9)


def solve():
    N, M = map(int, input().split())

    if N == 1:
        print(0)
        return

    adj = [[] for _ in range(N + 1)]
    for _ in range(M):
        A, B, D = map(int, input().split())
        adj[A].append((B, D))
        adj[B].append((A, D))

    def getMinDynamite(now: int, parent: int) -> int:
        minDynamite = 0

        for nxt, dynamite in adj[now]:
            if nxt == parent:
                continue

            minDynamite += min(getMinDynamite(nxt, now), dynamite)

        return minDynamite if minDynamite != 0 else INF

    print(getMinDynamite(1, -1))


def main():
    T = int(input())
    for _ in range(T):
        solve()


main()
