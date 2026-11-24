import sys

input = lambda: sys.stdin.readline().rstrip()

stairCount = int(input())
stairs = [int(input()) for _ in range(stairCount)]
score = [[0, 0] for _ in range(stairCount)]
if stairCount == 1:
    print(stairs[0])
    sys.exit(0)

score[0][0] = stairs[0]
score[1] = [stairs[1], stairs[0] + stairs[1]]

for i in range(2, stairCount):
    score[i][0] = max(
        (
            score[i - 2][0] + stairs[i],
            score[i - 2][1] + stairs[i],
        )
    )
    score[i][1] = max(
        (
            score[i - 2][0] + stairs[i],
            score[i - 2][1] + stairs[i],
            score[i - 1][0] + stairs[i],
        )
    )
print(max(score[-1]))
