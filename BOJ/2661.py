import sys

input = lambda: sys.stdin.readline().rstrip()


n = int(input())

seq = [1]


def dfs() -> bool:
    for size in range(1, len(seq) // 2 + 1):
        if (
            seq[len(seq) - size : len(seq)]
            == seq[len(seq) - size * 2 : len(seq) - size]
        ):
            return False

    if len(seq) == n:
        print(*seq, sep="")
        return True

    hasSucceed = False
    for i in range(1, 4):
        if hasSucceed:
            return True
        seq.append(i)
        hasSucceed = dfs()
        seq.pop()
    return hasSucceed


dfs()
