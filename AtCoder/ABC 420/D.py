from collections import deque

di = [1, -1, 0, 0]
dj = [0, 0, 1, -1]

H, W = map(int, input().split())
grid = [input() for _ in range(H)]

operCnt = [[[-1] * 2 for _ in range(W)] for _ in range(H)]

start = (0, 0)
goal = (0, 0)
for i in range(H):
    for j in range(W):
        if grid[i][j] == "S":
            start = (i, j)
        if grid[i][j] == "G":
            goal = (i, j)

si, sj = start
operCnt[si][sj][0] = 0

queue = deque([(start, 0)])
while queue:
    coord, switched = queue.popleft()
    i, j = coord

    for k in range(4):
        ni = i + di[k]
        nj = j + dj[k]

        if not (0 <= ni < H) or not (0 <= nj < W):
            continue
        if grid[ni][nj] == "#":
            continue
        if (switched and grid[ni][nj] == "o") or (not switched and grid[ni][nj] == "x"):
            continue

        nextSwitched = switched
        if grid[ni][nj] == "?":
            nextSwitched ^= 1

        if operCnt[ni][nj][nextSwitched] != -1:
            continue

        operCnt[ni][nj][nextSwitched] = operCnt[i][j][switched] + 1
        queue.append(((ni, nj), nextSwitched))

i, j = goal
answer = operCnt[i][j][0]

if operCnt[i][j][1] != -1:
    if answer == -1:
        answer = operCnt[i][j][1]
    else:
        answer = min(answer, operCnt[i][j][1])

print(answer)
