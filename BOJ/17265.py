def main():
    N = int(input())

    maximum = [[-10000] * N for _ in range(N)]
    minimum = [[10000] * N for _ in range(N)]

    grid = [input().split() for _ in range(N)]
    maximum[0][0] = int(grid[0][0])
    minimum[0][0] = int(grid[0][0])

    for i in range(N):
        for j in range(N):
            if grid[i][j].isdecimal():
                if j + 1 < N:
                    maximum[i][j + 1] = max(maximum[i][j + 1], maximum[i][j])
                    minimum[i][j + 1] = min(minimum[i][j + 1], minimum[i][j])
                if i + 1 < N:
                    maximum[i + 1][j] = max(maximum[i + 1][j], maximum[i][j])
                    minimum[i + 1][j] = min(minimum[i + 1][j], minimum[i][j])
            else:
                operator = lambda x, y: x * y
                if grid[i][j] == "+":
                    operator = lambda x, y: x + y
                elif grid[i][j] == "-":
                    operator = lambda x, y: x - y
                
                if j + 1 < N:
                    maximum[i][j + 1] = max(
                        maximum[i][j + 1], operator(maximum[i][j], int(grid[i][j + 1]))
                    )
                    minimum[i][j + 1] = min(
                        minimum[i][j + 1], operator(minimum[i][j], int(grid[i][j + 1]))
                    )
                if i + 1 < N:
                    maximum[i + 1][j] = max(
                        maximum[i + 1][j], operator(maximum[i][j], int(grid[i + 1][j]))
                    )
                    minimum[i + 1][j] = min(
                        minimum[i + 1][j], operator(minimum[i][j], int(grid[i + 1][j]))
                    )

    print(maximum[-1][-1], minimum[-1][-1])


main()
