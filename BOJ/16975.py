import sys
from math import ceil, log2

input = lambda: sys.stdin.readline().rstrip()


def init(array, tree, node, start, end):
    if start == end:
        tree[node] = array[start]
    else:
        mid = (start + end) // 2
        init(array, tree, node * 2, start, mid)
        init(array, tree, node * 2 + 1, mid + 1, end)


def update(tree, node, start, end, left, right, diff):
    if right < start or end < left:
        return
    if left <= start and end <= right:
        tree[node] += diff
        return

    mid = (start + end) // 2
    update(tree, node * 2, start, mid, left, right, diff)
    update(tree, node * 2 + 1, mid + 1, end, left, right, diff)


def query(tree, node, start, end, index, value):
    if index < start or end < index:
        return 0

    value += tree[node]
    if start == end:
        return value

    mid = (start + end) // 2
    lsum = query(tree, node * 2, start, mid, index, value)
    rsum = query(tree, node * 2 + 1, mid + 1, end, index, value)
    return lsum + rsum


N = int(input())
array = [0] + list(map(int, input().split()))
tree = [0] * (1 << (ceil(log2(N)) + 1))
init(array, tree, 1, 1, N)

for _ in range(int(input())):
    cmd, *others = map(int, input().split())

    if cmd == 1:
        left, right, diff = others
        update(tree, 1, 1, N, left, right, diff)
    else:
        x = others[0]
        print(query(tree, 1, 1, N, x, 0))
