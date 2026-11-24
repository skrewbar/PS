import sys

sys.setrecursionlimit(10**9)
input = lambda: sys.stdin.readline().rstrip()

n, k = map(int, input().split())
cannot = set(map(int, input().split()))

canwin = [None for _ in range(n + 1)]


def solve(x: int) -> int:
    if canwin[x] != None:
        return canwin[x]

    if x == n:
        canwin[x] = True
        return canwin[x]

    for i in range(x + 1, min(n + 1, x + k + 1)):
        if i in cannot:
            continue

        if solve(i):  # 상대가 이길 수 있으면
            canwin[x] = False
            return canwin[x]

    canwin[x] = True
    return canwin[x]


for i in range(1, min(n + 1, k + 1)):
    if not (i in cannot):
        solve(i)
        break

print(int(True in canwin[1 : k + 1]))
