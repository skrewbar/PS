import sys

sys.setrecursionlimit(10**8)
input = lambda: sys.stdin.readline().rstrip()


def main():
    N, M, K = map(int, input().split())

    adj = [[] for _ in range(N + 1)]
    for i in range(M):
        u, v = map(int, input().split())

        if i == K - 1:
            continue

        adj[u].append(v)
        adj[v].append(u)

    visited = [False] * (N + 1)

    def visit(now: int):
        visited[now] = True

        for nxt in adj[now]:
            if visited[nxt]:
                continue
            visit(nxt)

    visit(1)

    first = 0
    for i in range(1, N + 1):
        if visited[i]:
            first += 1

    firstVisited = list(visited)
    for i in range(1, N + 1):
        if not visited[i]:
            visit(i)

    second = 0
    for i in range(1, N + 1):
        if visited[i] and not firstVisited[i]:
            second += 1

    print(first * second)


main()
