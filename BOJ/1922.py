from heapq import *

parent: list[int] = None


def find_root(x: int) -> int:
    if x == parent[x]:
        return x
    else:
        parent[x] = find_root(parent[x])
        return parent[x]


def union_root(x: int, y: int) -> None:
    x = find_root(x)
    y = find_root(y)

    parent[x] = y


n = int(input())
m = int(input())

parent = [i for i in range(n + 1)]

lines = []
for _ in range(m):
    a, b, c = map(int, input().split())
    heappush(lines, (c, a, b))

mst_cost = 0
mst_line_count = 0

while mst_line_count != n - 1:
    line = heappop(lines)

    a, b = line[1], line[2]

    if find_root(a) != find_root(b):
        union_root(a, b)
        mst_cost += line[0]
        mst_line_count += 1

print(mst_cost)