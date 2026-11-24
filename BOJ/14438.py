from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()

N = int(input())
seq = list(map(int, input().split()))
h = ceil(log2(N))
tree = [0] * (1 << (h+1))

def init(node, start, end):
    if start == end:
        tree[node] = seq[start]
    else:
        mid = (start+end)//2
        init(node*2, start, mid)
        init(node*2+1, mid+1, end)
        tree[node] = min(tree[node*2], tree[node*2+1])

def change_tree(node, start, end, index, val):
    if index < start or end < index:
        return
    
    if start == end:
        seq[index] = val
        tree[node] = val
        return
    
    mid = (start+end)//2
    change_tree(node*2, start, mid, index, val)
    change_tree(node*2+1, mid+1, end, index, val)
    tree[node] = min(tree[node*2], tree[node*2+1])

def get_min(node, start, end, left, right):
    if right < start or end < left:
        return float("inf")
    if left <= start and end <= right:
        return tree[node]
    
    mid = (start+end)//2
    lmin = get_min(node*2, start, mid, left, right)
    rmin = get_min(node*2+1, mid+1, end, left, right)
    return min(lmin, rmin)

init(1, 0, N-1)
for _ in range(int(input())):
    query, *others = map(int, input().split())

    if query == 1:
        index, val = others
        change_tree(1, 0, N-1, index-1, val)
    else:
        left, right = others
        print(get_min(1, 0, N-1, left-1, right-1))