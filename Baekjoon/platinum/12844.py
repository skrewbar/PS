from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


N = int(input())
seq = list(map(int, input().split()))
tree_size = 1 << (ceil(log2(N)) + 1)
tree = [0] * tree_size
lazy = [0] * tree_size

def init(node, start, end):
    if start == end:
        tree[node] = seq[start]
    else:
        mid = (start + end) // 2
        init(node*2, start, mid)
        init(node*2+1, mid+1, end)
        tree[node] = tree[node*2] ^ tree[node*2+1]


def update_lazy(node, start, end):
    if lazy[node]:
        if (end - start + 1) % 2:
            tree[node] ^= lazy[node]
        if start != end:
            lazy[node*2] ^= lazy[node]
            lazy[node*2+1] ^= lazy[node]
        lazy[node] = 0


def update(node, start, end, left, right, val):
    update_lazy(node, start, end)
    if right < start or end < left:
        return
    if left <= start and end <= right:
        if (end - start + 1) % 2:
            tree[node] ^= val
        if start != end:
            lazy[node*2] ^= val
            lazy[node*2+1] ^= val
        return
    
    mid = (start + end) // 2
    update(node*2, start, mid, left, right, val)
    update(node*2+1, mid+1, end, left, right, val)
    tree[node] = tree[node*2] ^ tree[node*2+1]


def get_range_xor(node, start, end, left, right):
    update_lazy(node, start, end)
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    lxor = get_range_xor(node*2, start, mid, left, right)
    rxor = get_range_xor(node*2+1, mid+1, end, left, right)
    return lxor ^ rxor

init(1, 0, N-1)
for _ in range(int(input())):
    query, *others = map(int, input().split())

    if query == 1:
        left, right, val = others
        update(1, 0, N-1, left, right, val)
    else:
        left, right = others
        print(get_range_xor(1, 0, N-1, left, right))