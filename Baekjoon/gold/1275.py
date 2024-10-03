from math import log2, ceil

N, Q = map(int, input().split())

numbers = [0] + list(map(int, input().split()))
height = ceil(log2(N))
tree = [0] * (1 << (height+1))


def init(node, start, end):
    if start == end:
        tree[node] = numbers[start]
    else:
        mid = (start+end)//2
        init(node*2, start, mid)
        init(node*2+1, mid+1, end)
        tree[node] = tree[node*2] + tree[node*2+1]


def update_tree(node, start, end, index, diff):
    if index < start or end < index:
        return
    tree[node] += diff

    if start != end:
        mid = (start+end)//2
        update_tree(node*2, start, mid, index, diff)
        update_tree(node*2+1, mid+1, end, index, diff)


def get_range_sum(node, start, end, left, right):
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]
    
    mid = (start+end)//2
    lsum = get_range_sum(node*2, start, mid, left, right)
    rsum = get_range_sum(node*2+1, mid+1, end, left, right)
    return lsum + rsum

init(1, 1, N)
for _ in range(Q):
    x, y, a, b = map(int, input().split())
    if x > y:
        x, y = y, x #y가 항상 크도록 하기
    
    print(get_range_sum(1, 1, N, x, y))
    update_tree(1, 1, N, a, b-numbers[a])
    numbers[a] = b