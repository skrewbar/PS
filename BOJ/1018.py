import sys
from copy import deepcopy

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())
board = [list(input()) for _ in range(n)]
minRecolorCount = float("inf")


def getRecolorCount(
    originColor: str, originX: int, originY: int, board: list[list[int]]
):
    recolorCount = 0
    if board[originX][originY] != originColor:
        board[originX][originY] = originColor
        recolorCount += 1
    for x in range(originX, originX + 8):
        for y in range(originY, originY + 8):
            if y == originY:
                if x == originX:
                    continue
                else:
                    if board[x - 1][y] == board[x][y]:
                        if board[x][y] == "W":
                            board[x][y] = "B"
                        else:
                            board[x][y] = "W"
                        recolorCount += 1
            elif board[x][y - 1] == board[x][y]:
                if board[x][y] == "W":
                    board[x][y] = "B"
                else:
                    board[x][y] = "W"
                recolorCount += 1

    return recolorCount


for originX in range(n - 7):
    for originY in range(m - 7):
        minRecolorCount = min(
            [
                minRecolorCount,
                getRecolorCount("W", originX, originY, deepcopy(board)),
                getRecolorCount("B", originX, originY, deepcopy(board)),
            ]
        )
print(minRecolorCount)
