import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())

isExist = [False for i in range(10)]

DP = [
    [[0 for _ in range(1024)] for _ in range(10)] for _ in range(n + 1)
]  # DP[n+1][10][1024]

for j in range(1, 10):  # 0으로 시작하는 수는 계단수가 아니다.
    DP[1][j][1 << j] = 1

for i in range(2, n + 1):
    for j in range(10):
        for k in range(1024):
            if 0 < j < 9:
                DP[i][j][k | (1 << j)] += (
                    DP[i - 1][j - 1][k] + DP[i - 1][j + 1][k]
                ) % 1_000_000_000
            elif j == 0:
                DP[i][j][k | (1 << j)] += DP[i - 1][j + 1][k] % 1_000_000_000
            elif j == 9:
                DP[i][j][k | (1 << j)] += DP[i - 1][j - 1][k] % 1_000_000_000

count = 0
for j in range(10):
    count += DP[n][j][0b1111111111] % 1_000_000_000
print(count % 1_000_000_000)
