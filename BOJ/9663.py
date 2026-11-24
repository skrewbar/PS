import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())
queenColumn = [0 for i in range(n)]
answer = 0


def isAvailable(row: int) -> bool:
    for i in range(row):
        if queenColumn[row] == queenColumn[i] or abs(
            queenColumn[row] - queenColumn[i]
        ) == abs(row - i):
            return False
    return True


def dfs(row: int) -> None:
    global answer

    if row == n:
        answer += 1
        return

    for i in range(n):
        queenColumn[row] = i
        if isAvailable(row):
            dfs(row + 1)


dfs(0)
print(answer)
