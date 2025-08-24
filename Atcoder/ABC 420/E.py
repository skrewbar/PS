import sys

input = lambda: sys.stdin.readline().rstrip()


N, Q = map(int, input().split())

isWhite = [1] * (N + 1)
blackCnt = [0 for _ in range(N + 1)]
parent = [0] * (N + 1)
for i in range(1, N + 1):
    parent[i] = i


def findRoot(x: int):
    if x != parent[x]:
        parent[x] = findRoot(parent[x])
    return parent[x]


def unionRoot(u: int, v: int):
    u = findRoot(u)
    v = findRoot(v)
    if u == v:
        return
    parent[v] = u
    blackCnt[u] += blackCnt[v]


for _ in range(Q):
    qType, *args = map(int, input().split())

    if qType == 1:
        u, v = args
        unionRoot(u, v)
    if qType == 2:
        v = args[0]
        r = findRoot(v)
        if isWhite[v]:
            blackCnt[r] += 1
        else:
            blackCnt[r] -= 1
        isWhite[v] ^= 1
    if qType == 3:
        v = args[0]
        r = findRoot(v)
        print("Yes" if blackCnt[r] > 0 else "No")
