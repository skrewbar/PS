t = int(input())

for i in range(t):
    n = int(input())
    stickers = [list(map(int, input().split())), list(map(int, input().split()))]

    maxList = [stickers[0][0], stickers[1][0], 0]

    for i in range(1, n):
        max0, max1, maxNone = maxList
        maxList[0] = max(max1, maxNone) + stickers[0][i]
        maxList[1] = max(max0, maxNone) + stickers[1][i]
        maxList[2] = max(max0, max1)

    print(max(maxList))
