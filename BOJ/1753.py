import heapq
import sys

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())
start = int(input())
graph = [[] for i in range(n + 1)]
distance = [float("inf")] * (n + 1)

for _ in range(m):
    u, v, w = map(int, input().split())
    graph[u].append((v, w))


def dijkstra(start):
    queue = []
    heapq.heappush(queue, (0, start))
    distance[start] = 0

    while queue:
        curr_dist, current = heapq.heappop(queue)
        if distance[current] < curr_dist:
            continue
        for v, w in graph[current]:
            nxt_dist = curr_dist + w
            if nxt_dist < distance[v]:
                distance[v] = nxt_dist
                heapq.heappush(queue, (nxt_dist, v))


dijkstra(start)

for i in range(1, n + 1):
    print(str(distance[i]).upper())
