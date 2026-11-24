import sys

input = lambda: sys.stdin.readline().rstrip()

paper = []
for _ in range(n := int(input())):
    paper.append(list(map(int, input().split())))


def getPaperCount(left: int, right: int, up: int, down: int, color: int) -> int:
    if left == right and up == down:
        if paper[up][left] == color:
            return 1
        else:
            return 0

    for i in range(up, down + 1):
        for j in range(left, right + 1):
            if paper[i][j] != color:
                return (
                    getPaperCount(
                        left,
                        (left + right) // 2,
                        up,
                        (up + down) // 2,
                        color,
                    )
                    + getPaperCount(
                        (left + right) // 2 + 1,
                        right,
                        up,
                        (up + down) // 2,
                        color,
                    )
                    + getPaperCount(
                        left,
                        (left + right) // 2,
                        (up + down) // 2 + 1,
                        down,
                        color,
                    )
                    + getPaperCount(
                        (left + right) // 2 + 1,
                        right,
                        (up + down) // 2 + 1,
                        down,
                        color,
                    )
                )
    return 1


print(getPaperCount(0, n - 1, 0, n - 1, 0))
print(getPaperCount(0, n - 1, 0, n - 1, 1))
