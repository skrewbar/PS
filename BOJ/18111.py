import sys

input = lambda: sys.stdin.readline().rstrip()

row, column, b = map(int, input().split())

worldMap = []
for _ in range(row):
    worldMap.append(list(map(int, input().split())))

minTime = float("inf")
minTimeLevel = 0
for level in range(0, 257):
    time = 0
    blockCount = b
    for i in range(row):
        for j in range(column):
            if worldMap[i][j] < level:
                time += level - worldMap[i][j]
                blockCount -= level - worldMap[i][j]
            elif level < worldMap[i][j]:
                time += (worldMap[i][j] - level) * 2
                blockCount += worldMap[i][j] - level
    if blockCount < 0:
        break
    if time <= minTime:
        minTime = time
        minTimeLevel = level

print(minTime, minTimeLevel)
