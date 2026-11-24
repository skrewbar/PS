def main():
    n, m = map(int, input().split())

    grid = [list(map(lambda x: x.count("9"), input().split())) for _ in range(n)]

    totalNineCnt = 0
    for i in range(n):
        for j in range(m):
            totalNineCnt += grid[i][j]

    maxNineCnt = 0
    for i in range(n):
        nineCnt = 0
        for j in range(m):
            nineCnt += grid[i][j]

        maxNineCnt = max(maxNineCnt, nineCnt)
    for j in range(m):
        nineCnt = 0
        for i in range(n):
            nineCnt += grid[i][j]
        
        maxNineCnt = max(maxNineCnt, nineCnt)

    print(totalNineCnt - maxNineCnt)


main()
