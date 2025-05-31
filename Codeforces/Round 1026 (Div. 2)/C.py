for _ in range(int(input())):
    n = int(input())
    d = list(map(int, input().split()))
    obstacles = [list(map(int, input().split())) for _ in range(n)]

    for i in range(n - 1, 0, -1):
        l: int
        r: int

        if d[i] == -1:
            l = obstacles[i][0] - 1
            r = obstacles[i][1]
        else:
            l = obstacles[i][0] - d[i]
            r = obstacles[i][1] - d[i]

        obstacles[i - 1][0] = max(obstacles[i - 1][0], l)
        obstacles[i - 1][1] = min(obstacles[i - 1][1], r)

    solvable = True
    h = 0
    for i in range(n):
        l, r = obstacles[i]

        if d[i] == -1:
            d[i] = 1 if l <= h + 1 <= r else 0
        h += d[i]

        if not (l <= h <= r) or r < h:
            solvable = False
            break

    print(*(d if solvable else [-1]))
