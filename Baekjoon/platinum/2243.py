from math import ceil, log2
import sys

input = lambda: sys.stdin.readline().rstrip()


def get_flavor(tree, node, start, end, rank):
    if start == end:
        return start
    if rank <= tree[node * 2]:
        return get_flavor(tree, node * 2, start, (start + end) // 2, rank)
    else:
        return get_flavor(
            tree, node * 2 + 1, (start + end) // 2 + 1, end, rank - tree[node * 2]
        )


def update(tree, node, start, end, index, val):
    if index < start or end < index:
        return
    if start == end:
        tree[node] += val
        return
    update(tree, node * 2, start, (start + end) // 2, index, val)
    update(tree, node * 2 + 1, (start + end) // 2 + 1, end, index, val)
    tree[node] = tree[node * 2] + tree[node * 2 + 1]


flavors = 1000000

h = ceil(log2(flavors))
tree = [0] * (1 << (h + 1))

n = int(input())
for _ in range(n):
    a, *others = map(int, input().split())

    if a == 1:
        b = others[0]
        flavor = get_flavor(tree, 1, 0, flavors - 1, b)
        print(flavor + 1)
        update(tree, 1, 0, flavors - 1, flavor, -1)
    else:
        b, c = others
        update(tree, 1, 0, flavors - 1, b - 1, c)
