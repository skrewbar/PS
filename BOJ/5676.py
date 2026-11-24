from math import log2, ceil
import sys

input = lambda: sys.stdin.readline().rstrip()


def init(seq, tree, node, start, end):
    if start == end:
        tree[node] = seq[start]
    else:
        mid = (start+end)//2
        init(seq, tree, node*2, start, mid)
        init(seq, tree, node*2+1, mid+1, end)
        tree[node] = tree[node*2] * tree[node*2+1]

def change_tree(seq, tree, node, start, end, index, val):
    if index < start or end < index:
        return
    if start == end:
        tree[node] = val
        return
    
    mid = (start+end)//2
    change_tree(seq, tree, node*2, start, mid, index, val)
    change_tree(seq, tree, node*2+1, mid+1, end, index, val)
    tree[node] = tree[node*2] * tree[node*2+1]

def get_range_mul(seq, tree, node, start, end, left, right):
    if right < start or end < left:
        return 1
    if left <= start and end <= right:
        return tree[node]

    mid = (start+end)//2
    lmul = get_range_mul(seq, tree, node*2, start,  mid, left, right)
    rmul = get_range_mul(seq, tree, node*2+1, mid+1, end, left, right)
    return lmul * rmul

def num_to_sign(num):
    num = int(num)
    if num > 0:
        return 1
    if num < 0:
        return -1
    return 0

while True:
    try:
        N, K = map(int, input().split())
        seq = list(map(num_to_sign, input().split()))
        h = ceil(log2(N))
        tree = [0] * (1 << (h+1))

        init(seq, tree, 1, 0, N-1)

        for _ in range(K):
            query, *others = input().split()

            if query == "C":
                index, val = map(int, others)
                val = num_to_sign(val)
                change_tree(seq, tree, 1, 0, N-1, index-1, val)
            else:
                left, right = map(int, others)
                res = get_range_mul(seq, tree, 1, 0, N-1, left-1, right-1)
                if res > 0:
                    print("+", end="")
                elif res < 0:
                    print("-", end="")
                else:
                    print("0", end="")
        print()
    except:
        break