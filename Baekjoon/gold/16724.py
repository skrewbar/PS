n, m = map(int, input().split())

map_ = [list(input()) for _ in range(n)]  # '#' is visited


def is_in_cycle(map_: list[list[str | int]], i: int, j: int, key: int) -> bool:
    x, y = i, j

    while True:
        direction = map_[x][y]
        map_[x][y] = key
        match direction:
            case "U":
                x -= 1
            case "D":
                x += 1
            case "L":
                y -= 1
            case "R":
                y += 1

        if type(map_[x][y]) != str:  # '#' means visited
            break

    return not map_[x][y] == map_[i][j]


answer = 0
key = 0
for i in range(n):
    for j in range(m):
        if type(map_[i][j]) != str:
            continue
        answer += not is_in_cycle(map_, i, j, key := key + 1)
        # print(*map_, sep="\n")
        # print()
print(answer)
