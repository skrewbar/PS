import sys

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())

board = []
for _ in range(n):
    board.append(list(map(int, input().split())))

prefix_sum = [[0] * n + [0]]
for i in board:
    prefix_sum.append([0] + i)

for i in range(1, n + 1):
    for j in range(1, n + 1):
        prefix_sum[i][j] = (
            prefix_sum[i][j - 1]
            + prefix_sum[i - 1][j]
            - prefix_sum[i - 1][j - 1]
            + board[i - 1][j - 1]
        )

for _ in range(m):
    x1, y1, x2, y2 = map(int, input().split())
    print(
        prefix_sum[x2][y2]
        - prefix_sum[x1 - 1][y2]
        - prefix_sum[x2][y1 - 1]
        + prefix_sum[x1 - 1][y1 - 1]
    )
