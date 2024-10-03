import sys

sys.setrecursionlimit(10**6)
input = lambda: sys.stdin.readline().rstrip()


n, m = map(int, input().split())

parent = [i for i in range(n + 1)]


def findParent(a):
    if a != parent[a]:
        parent[a] = findParent(parent[a])
    return parent[a]


def union(a, b):
    a = findParent(a)  # 각각의 부모 노드
    b = findParent(b)

    if b < a:
        parent[a] = b
    else:
        parent[b] = a


for _ in range(m):
    cmd, a, b = map(int, input().split())
    if cmd == 0:
        union(a, b)
    else:
        if findParent(a) == findParent(b):
            print("YES")
        else:
            print("NO")
