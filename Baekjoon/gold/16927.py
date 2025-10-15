def main():
    N, M, R = map(int, input().split())
    A = [list(map(int, input().split())) for _ in range(N)]

    def rotate(start: tuple[int, int], end: tuple[int, int], dr: int, dc: int):
        r, c = start
        while (r, c) != end:
            nr = r + dr
            nc = c + dc

            A[r][c], A[nr][nc] = A[nr][nc], A[r][c]

            r, c = nr, nc

    r, c = 0, 0
    while r < N - 1 - r and c < M - 1 - c:
        cnt = R % (2 * (N - 2 * r) + 2 * (M - 2 * c) - 4)

        for _ in range(cnt):
            rotate((r, c), (r, M - 1 - c), 0, 1)
            rotate((r, M - 1 - c), (N - 1 - r, M - 1 - c), 1, 0)
            rotate((N - 1 - r, M - 1 - c), (N - 1 - r, c), 0, -1)
            rotate((N - 1 - r, c), (r + 1, c), -1, 0)

        r += 1
        c += 1

    for row in A:
        print(*row)


main()
