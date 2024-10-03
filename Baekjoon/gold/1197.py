import sys
from heapq import *

input = lambda: sys.stdin.readline().rstrip()


def find_root(x: int) -> int:
    if parent[x] == x:
        return x
    else:
        parent[x] = find_root(parent[x])
        return parent[x]


def union_root(x: int, y: int) -> None:
    rootX = find_root(x)
    rootY = find_root(y)

    if rootX != rootY:
        parent[rootX] = rootY


vertexCount, edgeCount = map(int, input().split())

parent = [i for i in range(vertexCount + 1)]
edges: list[tuple[int, int, int]] = []  # (cost, a, b)

for _ in range(edgeCount):
    a, b, c = map(int, input().split())
    heappush(edges, (c, a, b))

mstCost = 0
mstEdgeCount = 0
while True:
    edge = heappop(edges)

    a, b = edge[1], edge[2]

    if find_root(a) != find_root(b):
        mstCost += edge[0]
        union_root(a, b)
        mstEdgeCount += 1

    if mstEdgeCount == vertexCount - 1:
        break

print(mstCost)