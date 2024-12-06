r, c, t = map(int, input().split())

house = [list(map(int, input().split())) for _ in range(r)]
lazy = [[0] * c for _ in range(r)]


def spread(i: int, j: int) -> None:
    count = 0
    amount = house[i][j] // 5

    for k in range(4):
        ni = i + [0, 0, 1, -1][k]
        nj = j + [1, -1, 0, 0][k]
        if 0 <= ni < r and 0 <= nj < c and house[ni][nj] != -1:
            lazy[ni][nj] += amount
            count += 1

    house[i][j] -= count * amount


UP = (-1, 0)
RIGHT = (0, 1)
DOWN = (1, 0)
LEFT = (0, -1)


def upclear(i: int) -> None:
    direction = UP

    x, y = i - 1, 0
    house[x][y] = 0

    while (x, y) != (i, 1):
        if x == 0 and y == 0:
            direction = RIGHT
        elif x == 0 and y == c - 1:
            direction = DOWN
        elif x == i and y == c - 1:
            direction = LEFT

        dx, dy = direction
        house[x][y] = house[x + dx][y + dy]
        x += dx
        y += dy

    house[i][1] = 0


def downclear(i: int) -> None:
    direction = DOWN

    x, y = i + 1, 0
    house[x][y] = 0

    while (x, y) != (i, 1):
        if x == r - 1 and y == 0:
            direction = RIGHT
        elif x == r - 1 and y == c - 1:
            direction = UP
        elif x == i and y == c - 1:
            direction = LEFT

        dx, dy = direction
        house[x][y] = house[x + dx][y + dy]
        x += dx
        y += dy

    house[i][1] = 0


fresher: tuple[int, int]
for i in range(r):
    if house[i][0] == -1:
        fresher = (i, i + 1)
        break


for _ in range(t):
    for i in range(r):
        for j in range(c):
            if i in fresher and j == 0:
                continue
            spread(i, j)

    for i in range(r):
        for j in range(c):
            if i in fresher and j == 0:
                continue
            house[i][j] += lazy[i][j]
            lazy[i][j] = 0

    upclear(fresher[0])
    downclear(fresher[1])

# for i in range(r):
#     print(*house[i])

ans = sum([sum(house[i]) for i in range(r)])
print(ans + 2)
