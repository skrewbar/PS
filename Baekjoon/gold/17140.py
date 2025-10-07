r, c, k = map(int, input().split())

mat = [[0] * 4 for _ in range(4)]
for i in range(1, 4):
    for j, v in enumerate(map(int, input().split()), 1):
        mat[i][j] = v


def extendRow():
    mat.append([0] * len(mat[1]))


def extendCol():
    for i in range(1, len(mat)):
        mat[i].append(0)


def sortRow(i: int):
    count: dict[int, int] = {}

    for j in range(1, len(mat[i])):
        if mat[i][j] not in count:
            count[mat[i][j]] = 0
        count[mat[i][j]] += 1

    if 0 in count:
        del count[0]

    j = 1
    for k in sorted(count, key=lambda x: (count[x], x)):
        while j + 1 >= len(mat[i]):
            extendCol()

        mat[i][j] = k
        mat[i][j + 1] = count[k]
        j += 2

    while j < len(mat[1]):
        mat[i][j] = 0
        j += 1


def sortCol(j: int):
    count: dict[int, int] = {}

    for i in range(1, len(mat)):
        if mat[i][j] not in count:
            count[mat[i][j]] = 0
        count[mat[i][j]] += 1

    if 0 in count:
        del count[0]

    i = 1
    for k in sorted(count, key=lambda x: (count[x], x)):
        while i + 1 >= len(mat):
            extendRow()

        mat[i][j] = k
        mat[i + 1][j] = count[k]
        i += 2

    while i < len(mat):
        mat[i][j] = 0
        i += 1


t = 0
while t <= 100:
    if r < len(mat) and c < len(mat[1]) and mat[r][c] == k:
        break

    if len(mat) >= len(mat[1]):
        for i in range(1, len(mat)):
            sortRow(i)
    else:
        for j in range(1, len(mat[1])):
            sortCol(j)

    t += 1

print(t if t <= 100 else -1)
