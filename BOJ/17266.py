def solve():
    N = int(input())
    M = int(input())
    x = list(map(int, input().split()))

    height = x[0]
    lightBound = x[0] + height
    for i in range(1, M):
        while lightBound < x[i] - height:
            height += 1
            lightBound += 1
        lightBound = x[i] + height

    if x[-1] + height < N:
        height = N - x[-1]

    print(height)


solve()
