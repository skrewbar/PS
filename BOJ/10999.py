import sys
from math import log2, ceil

input = lambda: sys.stdin.readline().rstrip()


def init(array: list[int], tree: list[int], node: int, start: int, end: int) -> None:
    if start == end:
        tree[node] = array[start]
    else:
        init(array, tree, node * 2, start, (start + end) // 2)
        init(array, tree, node * 2 + 1, (start + end) // 2 + 1, end)
        tree[node] = tree[node * 2] + tree[node * 2 + 1]


def lazy_update(
    tree: list[int], lazy: list[int], node: int, start: int, end: int
) -> None:
    if lazy[node] != 0:
        tree[node] += (end - start + 1) * lazy[node]

        if start != end:
            lazy[node * 2] += lazy[node]
            lazy[node * 2 + 1] += lazy[node]
        lazy[node] = 0


def range_update(
    tree: list[int],
    lazy: list[int],
    node: int,
    start: int,
    end: int,
    left: int,
    right: int,
    diff: int,
):
    lazy_update(tree, lazy, node, start, end)

    if right < start or end < left:
        return
    if left <= start and end <= right:
        tree[node] += (end - start + 1) * diff
        if start != end:
            lazy[node * 2] += diff
            lazy[node * 2 + 1] += diff
        return

    range_update(tree, lazy, node * 2, start, (start + end) // 2, left, right, diff)
    range_update(
        tree, lazy, node * 2 + 1, (start + end) // 2 + 1, end, left, right, diff
    )
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


def query(
    tree: list[int],
    lazy: list[int],
    node: int,
    start: int,
    end: int,
    left: int,
    right: int,
):
    lazy_update(tree, lazy, node, start, end)
    if right < start or end < left:
        return 0
    if left <= start and end <= right:
        return tree[node]
    lsum = query(tree, lazy, node * 2, start, (start + end) // 2, left, right)
    rsum = query(tree, lazy, node * 2 + 1, (start + end) // 2 + 1, end, left, right)
    return lsum + rsum


N, M, K = map(int, input().split())
array = [0] + [int(input()) for _ in range(N)]

h = ceil(log2(N))
tree_size = 1 << (h + 1)
tree = [0] * tree_size
lazy = [0] * tree_size
init(array, tree, 1, 1, N)

for _ in range(M+K):
    a, *others = map(int, input().split())

    if a == 1:
        b, c, d = others
        range_update(tree, lazy, 1, 1, N, b, c, d)
    else:
        b, c = others
        print(query(tree, lazy, 1, 1, N, b, c))
