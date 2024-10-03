# 세그먼트 트리 활용 문제
import sys
from math import log2, ceil

input = lambda: sys.stdin.readline().rstrip()


# 트리 생성 함수
def init(array: list[int], tree: list[int], node: int, start: int, end: int) -> None:
    if start == end:
        tree[node] = array[start]
    else:
        init(array, tree, node * 2, start, (start + end) // 2)
        init(array, tree, node * 2 + 1, (start + end) // 2 + 1, end)
        tree[node] = tree[node * 2] + tree[node * 2 + 1]


# 구간 합 구하는 함수
def query(
    tree: list[int], node: int, start: int, end: int, left: int, right: int
) -> int:
    if right < start or end < left:
        return 0
    elif left <= start and end <= right:
        return tree[node]

    lsum = query(tree, node * 2, start, (start + end) // 2, left, right)
    rsum = query(tree, node * 2 + 1, (start + end) // 2 + 1, end, left, right)
    return lsum + rsum


# 트리의 노드 변경 함수
def update(
    array: list[int],
    tree: list[int],
    node: int,
    start: int,
    end: int,
    index: int,
    value: int,
) -> None:
    if index < start or end < index:
        return
    if start == end:
        array[index] = value
        tree[node] = value
        return

    update(array, tree, node * 2, start, (start + end) // 2, index, value)
    update(array, tree, node * 2 + 1, (start + end) // 2 + 1, end, index, value)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


N, M, K = map(int, input().split())

numbers = [0] + [int(input()) for _ in range(N)]  # N개의 수 입력받기

h = ceil(log2(N))  # 세그먼트 트리의 높이 구하기
tree = [0] * (1 << (h + 1))
init(numbers, tree, 1, 1, N)  # 트리 구현

for _ in range(M + K):
    a, b, c = map(int, input().split())

    if a == 1:
        update(numbers, tree, 1, 1, N, b, c)
    else:
        print(query(tree, 1, 1, N, b, c))
