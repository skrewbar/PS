LEFT, DOWN, RIGHT, UP = range(4)

dr = [0, 1, 0, -1]
dc = [-1, 0, 1, 0]

routes = [  # starts from cell "y"
    # (rotates, ratio)
    # rotates: sequence of counterclockwise turns (with forward movement after each)
    # ratio: sand distribution ratio
    ((3, 0), 2),
    ((0, 3), 10),
    ((3,), 7),
    ((3, 3), 1),
    ((0, 0), 5),
    ((1, 1), 1),
    ((1,), 7),
    ((0, 1), 10),
    ((1, 0), 2),
]


def main():
    N = int(input())

    def isInGrid(r: int, c: int) -> bool:
        return 0 <= r < N and 0 <= c < N

    sands = [list(map(int, input().split())) for _ in range(N)]
    visited = [[False] * N for _ in range(N)]

    r = N // 2
    c = r
    visited[r][c] = True

    d = UP  # direction
    out = 0

    while (r, c) != (0, 0):
        d = (d + 1) % 4
        nr = r + dr[d]
        nc = c + dc[d]

        if visited[nr][nc]:
            d = (d - 1) % 4
            nr = r + dr[d]
            nc = c + dc[d]

        r, c = nr, nc
        visited[r][c] = True

        accumulate = 0
        for rotates, ratio in routes:
            dd = d
            nr, nc = r, c

            for rotate in rotates:
                dd = (dd + rotate) % 4
                nr += dr[dd]
                nc += dc[dd]

            amount = sands[r][c] * ratio // 100
            accumulate += amount
            if isInGrid(nr, nc):
                sands[nr][nc] += amount
            else:
                out += amount

        nr = r + dr[d]
        nc = c + dc[d]

        amount = sands[r][c] - accumulate
        sands[r][c] = 0
        if isInGrid(nr, nc):
            sands[nr][nc] += amount
        else:
            out += amount

    print(out)


main()
