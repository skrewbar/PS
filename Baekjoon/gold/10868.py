from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()

N, M = map(int, input().split())
seq = [int(input()) for _ in range(N)]
h = ceil(log2(N))
tree = [0] * (1 << (h + 1))


def init(node, start, end):
    if start == end:
        tree[node] = seq[start]
    else:
        mid = (start + end) // 2
        init(node * 2, start, mid)
        init(node * 2 + 1, mid + 1, end)
        tree[node] = min(tree[node * 2], tree[node * 2 + 1])


def get_range_min(node, start, end, left, right):
    if right < start or end < left:
        return float("inf")
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    lmin = get_range_min(node * 2, start, mid, left, right)
    rmin = get_range_min(node * 2 + 1, mid + 1, end, left, right)
    return min(lmin, rmin)


init(1, 0, N - 1)
for _ in range(M):
    left, right = map(int, input().split())
    print(get_range_min(1, 0, N - 1, left - 1, right - 1))
