from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


N = int(input())
seq = list(map(int, input().split())) + [0]  # seq[-1] = 0
tree_size = 1 << (ceil(log2(N)) + 1)
tree = [0] * tree_size
lazy = [0] * tree_size


def init(node, start, end):
    if start == end:
        tree[node] = seq[start] - seq[start - 1]
    else:
        init(node * 2, start, (start + end) // 2)
        init(node * 2 + 1, (start + end) // 2 + 1, end)
        tree[node] = tree[node * 2] + tree[node * 2 + 1]


def update_lazy(node, start, end):
    if lazy[node] != 0:
        tree[node] += (end - start + 1) * lazy[node]
        if start != end:
            lazy[node * 2] += lazy[node]
            lazy[node * 2 + 1] += lazy[node]
        lazy[node] = 0


def update_index(node, start, end, index, val):
    update_lazy(node, start, end)
    if index < start or end < index:
        return
    if start == end:
        tree[node] -= val
        return
    update_index(node * 2, start, (start + end) // 2, index, val)
    update_index(node * 2 + 1, (start + end) // 2 + 1, end, index, val)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


def update_range(node, start, end, left, right):
    update_lazy(node, start, end)
    if right < start or end < left:
        return
    if left <= start and end <= right:
        tree[node] += end - start + 1
        if start != end:
            lazy[node * 2] += 1
            lazy[node * 2 + 1] += 1
        return
    update_range(node * 2, start, (start + end) // 2, left, right)
    update_range(node * 2 + 1, (start + end) // 2 + 1, end, left, right)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


def get_range_sum(node, start, end, index):
    update_lazy(node, start, end)
    if index < start:
        return 0
    if end <= index:
        return tree[node]

    lval = get_range_sum(node * 2, start, (start + end) // 2, index)
    rval = get_range_sum(node * 2 + 1, (start + end) // 2 + 1, end, index)
    return lval + rval


init(1, 0, N - 1)
for _ in range(int(input())):
    query, *others = map(int, input().split())
    if query == 1:
        left, right = others
        update_range(1, 0, N - 1, left - 1, right - 1)
        update_index(1, 0, N - 1, right, right - left + 1)
    else:
        index = others[0]
        print(get_range_sum(1, 0, N - 1, index - 1))
