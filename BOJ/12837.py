from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()

N, Q = map(int, input().split())
seq = [0] * N
tree = [0] * (1 << (ceil(log2(N)) + 1))


def init(node, start, end):
    if start == end:
        tree[node] = seq[start]
    else:
        mid = (start + end) // 2
        init(node*2, start, mid)
        init(node*2+1, mid+1, end)
        tree[node] = tree[node*2] + tree[node*2+1]


def update(node, start, end, index, val):
    if index < start or end < index:
        return
    if start == end:
        tree[node] += val
        return
    mid = (start + end) // 2
    update(node*2, start, mid, index, val)
    update(node*2+1, mid+1, end, index, val)
    tree[node] = tree[node*2] + tree[node*2+1]


def get_sum(node, start, end, left, right):
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]
    mid = (start + end) // 2
    lsum = get_sum(node*2, start, mid, left, right)
    rsum = get_sum(node*2+1, mid+1, end, left, right)
    return lsum + rsum


init(1, 0, N - 1)
for _ in range(Q):
    print(tree)
    query, p, q = map(int, input().split())
    if query == 1:
        update(1, 0, N - 1, p - 1, q)
    else:
        print(get_sum(1, 0, N - 1, p - 1, q - 1))
