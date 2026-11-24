from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


n = int(input())
seq = list(map(int, input().split()))
h = ceil(log2(n))
tree = [0] * (1 << (h + 1))

def init(node, start, end):
    if start == end:
        tree[node] = seq[start]
    else:
        mid = (start + end) // 2
        init(node*2, start, mid)
        init(node*2+1, mid+1, end)
    #리프 노드만 초기화


def update(node, start, end, left, right, val):
    if right < start or end < left:
        return
    if left <= start and end <= right:
        tree[node] ^= val
        return
    
    mid = (start + end) // 2
    update(node*2, start, mid, left, right, val)
    update(node*2+1, mid+1, end, left, right, val)


def get_number(node, start, end, index):
    if index < start or end < index:
        return 0
    
    if start == end:
        return tree[node]
    
    mid = (start + end) // 2
    lxor = get_number(node*2, start, mid, index)
    rxor = get_number(node*2+1, mid+1, end, index)
    return tree[node] ^ lxor ^ rxor

init(1, 0, n-1)
for _ in range(int(input())):
    query, *others = map(int, input().split())
    
    if query == 1:
        left, right, val = others
        update(1, 0, n-1, left, right, val)
    else:
        index = others[0]
        print(get_number(1, 0, n-1, index))