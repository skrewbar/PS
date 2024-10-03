from math import log2, ceil
import sys

N, M = map(int, input().split())
seq = [0] + [0 for i in range(N)]
h = ceil(log2(N))
tree = [0] * (1 << (h+1))

def get_range_sum(node, start, end, left, right):
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]

    mid = (start+end)//2
    lsum = get_range_sum(node*2, start, mid, left, right)
    rsum = get_range_sum(node*2+1, mid+1, end, left, right)
    return lsum + rsum

def change_num(node, start, end, index, val):
    if index < start or end < left:
        return
    if start == end:
        seq[index] = val
        tree[node] = val
        return
    
    mid = (start+end)//2
    change_num(node*2, start, mid, index, val)
    change_num(node*2+1, mid+1, end, index, val)
    tree[node] = tree[node*2] + tree[node*2+1]

for _ in range(M):
    query, *others = map(int, input().split())

    if query == 0:
        left, right = others
        print(get_range_sum(1, 1, N, left, right))
    else:
        index, val = others
        change_num(1, 1, N, index, val)