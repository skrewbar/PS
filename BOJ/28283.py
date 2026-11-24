import sys
import heapq
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, M, X, Y = map(int, input().split())
    A = [0] + list(map(int, input().split()))

    adj = [[] for _ in range(N + 1)]
    for _ in range(M):
        S, E = map(int, input().split())
        adj[S].append(E)
        adj[E].append(S)

    time = [-1] * (N + 1)
    queue = deque()
    for i in map(int, input().split()):
        time[i] = 0
        queue.append(i)
    profits = []

    while queue:
        now = queue.popleft()

        for nxt in adj[now]:
            if time[nxt] != -1:
                continue

            time[nxt] = time[now] + 1
            profit = time[nxt] * A[nxt]
            heapq.heappush(profits, profit)
            if len(profits) > X:
                heapq.heappop(profits)

            queue.append(nxt)

    for i in range(1, N + 1):
        if time[i] == -1 and A[i] > 0:
            print(-1)
            return

    print(sum(profits))


main()
