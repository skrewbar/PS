from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


N = int(input())
seq = list(map(int, input().split()))
h = ceil(log2(N))
tree_size = 1 << (h + 1)
tree = [0] * tree_size

def merge_tuple(t1, t2):
    merged = (t1[0] + t2[0], t1[1] + t2[1])
    return merged


def init(node, start, end):
    if start == end: #리프 노드
        if seq[start] % 2:
            tree[node] = (0, 1) # 짝수개수, 홀수개수
        else:
            tree[node] = (1, 0)
    else:
        mid = (start + end) // 2
        init(node*2, start, mid)
        init(node*2+1, mid+1, end)
        tree[node] = merge_tuple(tree[node*2], tree[node*2+1])


def update(node, start, end, index, val):
    if index < start or end < index:
        return
    if start == end:
        if val % 2:
            tree[node] = (0, 1)
        else:
            tree[node] = (1, 0)
        return
    
    mid = (start + end) // 2
    update(node*2, start, mid, index, val)
    update(node*2+1, mid+1, end, index, val)
    tree[node] = merge_tuple(tree[node*2], tree[node*2+1])


def get_count(node, start, end, left, right):
    if right < start or end < left:
        return (0, 0)
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    lcount = get_count(node*2, start, mid, left, right)
    rcount = get_count(node*2+1, mid+1, end, left, right)
    return merge_tuple(lcount, rcount)

init(1, 0, N-1)
for _ in range(int(input())):
    query, *others = map(int, input().split())
    if query == 1:
        index, val = others
        update(1, 0, N-1, index-1, val)
    else:
        left, right = others
        print(get_count(1, 0, N-1, left-1, right-1)[query-2])