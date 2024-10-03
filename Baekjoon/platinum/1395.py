from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


N, M = map(int, input().split())
seq = [0] * N
h = ceil(log2(N))
tree = [0] * (1 << (h + 1))
lazy = [0] * (1 << (h + 1))


def lazy_update(node, start, end):
    if lazy[node]:
        tree[node] = end - start + 1 - tree[node]
        if start != end:
            lazy[node*2] ^= 1
            lazy[node*2+1] ^= 1
        lazy[node] = 0


def reversal(node, start, end, left, right):
    lazy_update(node, start, end)
    if right < start or end < left:
        return
    if left <= start and end <= right:
        tree[node] = end - start + 1 - tree[node]
        if start != end:
            lazy[node*2] ^= 1
            lazy[node*2+1] ^= 1
        return
    
    mid = (start + end) // 2
    reversal(node*2, start, mid, left, right)
    reversal(node*2+1, mid+1, end, left, right)
    tree[node] = tree[node*2] + tree[node*2+1]


def get_light_count(node, start, end, left, right):
    lazy_update(node, start, end)
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    lcount = get_light_count(node*2, start, mid, left, right)
    rcount = get_light_count(node*2+1, mid+1, end, left, right)
    return lcount + rcount


for _ in range(M):
    query, left, right = map(int, input().split())

    if query == 0:
        reversal(1, 0, N-1, left-1, right-1)
    else:
        print(get_light_count(1, 0, N-1, left-1, right-1), end=" ")