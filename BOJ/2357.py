from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


N, M = map(int, input().split())
seq = [int(input()) for _ in range(N)]
tree = [0] * (1 << (ceil(log2(N)) + 1))


def merge_tuple(t1, t2):
    return (min(t1[0], t2[0]), max(t1[1], t2[1]))  # (최소, 최대)


def init(node, start, end):
    if start == end:
        tree[node] = (seq[start], seq[start])
    else:
        mid = (start + end) // 2
        init(node * 2, start, mid)
        init(node * 2 + 1, mid + 1, end)
        tree[node] = merge_tuple(tree[node * 2], tree[node * 2 + 1])


def get_range_mm(node, start, end, left, right):
    if right < start or end < left:
        return (float("inf"), 0)
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    lmm = get_range_mm(node * 2, start, mid, left, right)
    rmm = get_range_mm(node * 2 + 1, mid + 1, end, left, right)
    return merge_tuple(lmm, rmm)


init(1, 0, N - 1)
for _ in range(M):
    left, right = map(int, input().split())
    if left > right:
        left, right = right, left
    mm = get_range_mm(1, 0, N - 1, left - 1, right - 1)
    print(*mm)
