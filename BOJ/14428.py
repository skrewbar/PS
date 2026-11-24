from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


N = int(input())
tree = [0] * (1 << (ceil(log2(N)) + 1))
seq = list(map(int, input().split())) + [float("inf")]


def get_min_index(i: int, j: int) -> int:
    if seq[i] < seq[j]:
        return i
    elif seq[j] < seq[i]:
        return j
    else:
        return min(i, j)


def init(node: int, start: int, end: int) -> None:
    if start == end:
        tree[node] = start  # 인덱스 저장
    else:
        mid = (start + end) // 2
        init(node * 2, start, mid)
        init(node * 2 + 1, mid + 1, end)
        tree[node] = get_min_index(tree[node * 2], tree[node * 2 + 1])


def update_tree(node: int, start: int, end: int, index: int) -> None:
    if index < start or end < index:
        return
    if start == end:
        return  # 리프 노드는 바뀔 일 없음

    mid = (start + end) // 2
    update_tree(node * 2, start, mid, index)
    update_tree(node * 2 + 1, mid + 1, end, index)
    tree[node] = get_min_index(tree[node * 2], tree[node * 2 + 1])


def get_range_min(node: int, start: int, end: int, left: int, right: int) -> int:
    if right < start or end < left:
        return -1
    if left <= start and end <= right:
        return tree[node]

    mid = (start + end) // 2
    lmin = get_range_min(node * 2, start, mid, left, right)
    rmin = get_range_min(node * 2 + 1, mid + 1, end, left, right)
    return get_min_index(lmin, rmin)


init(1, 0, N - 1)
for _ in range(int(input())):
    query, *others = map(int, input().split())

    if query == 1:
        index, val = others
        seq[index - 1] = val
        update_tree(1, 0, N - 1, index - 1)
    else:
        left, right = others
        print(get_range_min(1, 0, N - 1, left - 1, right - 1) + 1)
