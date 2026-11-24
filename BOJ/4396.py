n = int(input())
mineMap = [list(input()) for i in range(n)]
playedMap = [list(input()) for i in range(n)]
mineCountMap = [[0 for i in range(n)] for i in range(n)]
isFailed = False

iL = [-1, -1, -1, 0, 0, 0, 1, 1, 1]
jL = [-1, 0, 1, -1, 0, 1, -1, 0, 1]

for i in range(n):
    for j in range(n):
        if mineMap[i][j] == "*":
            for k in range(9):
                ni = i + iL[k]
                nj = j + jL[k]

                if (0 <= ni < n) and (0 <= nj < n):
                    mineCountMap[ni][nj] += 1

            if playedMap[i][j] == "x":
                isFailed = True

for i in range(n):
    for j in range(n):
        (
            print("*", end="")
            if (mineMap[i][j] == "*" and isFailed)
            else print([".", mineCountMap[i][j]][int(playedMap[i][j] == "x")], end="")
        )
    print()
