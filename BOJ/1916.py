import heapq
import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())
m = int(input())
graph = [[] for _ in range(n + 1)]
distances = [float("inf")] * (n + 1)

for _ in range(m):
    a, b, c = map(int, input().split())
    graph[a].append((b, c))

start, end = map(int, input().split())


def dijkstra(start):
    queue = [(0, start)]
    distances[start] = 0

    while queue:
        curr_dist, current = heapq.heappop(queue)
        if distances[current] < curr_dist:
            continue
        for nxt, now_nxt_dist in graph[current]:
            nxt_dist = curr_dist + now_nxt_dist
            if nxt_dist < distances[nxt]:
                distances[nxt] = nxt_dist
                heapq.heappush(queue, (nxt_dist, nxt))


dijkstra(start)
print(distances[end])
