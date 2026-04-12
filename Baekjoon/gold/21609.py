from collections import deque


delta = [1, -1, 0, 0]

EMPTY = -2
BLACK = -1
RAINBOW = 0


def main():
    N, M = map(int, input().split())
    grid = [list(map(int, input().split())) for _ in range(N)]

    def pull_down_grid():
        for r in range(N - 2, -1, -1):
            for c in range(N):
                if grid[r][c] == BLACK:
                    continue

                nr = r
                while not is_invalid(nr + 1, c) and grid[nr + 1][c] == EMPTY:
                    nr += 1
                if nr != r:
                    grid[nr][c] = grid[r][c]
                    grid[r][c] = EMPTY

    def rotate_grid():
        nonlocal grid

        new_grid = [[EMPTY] * N for _ in range(N)]
        for r in range(N):
            for c in range(N):
                new_grid[N - c - 1][r] = grid[r][c]

        grid = new_grid

    def counter():
        total = 0
        rainbow = 0

        def get_total_count():
            return total

        def get_rainbow_count():
            return rainbow

        def count(r: int, c: int):
            nonlocal total, rainbow

            total += 1
            rainbow += 1 if grid[r][c] == RAINBOW else 0

        return get_total_count, get_rainbow_count, count

    def empty(r: int, c: int):
        grid[r][c] = EMPTY

    def is_invalid(r: int, c: int) -> bool:
        return r < 0 or r >= N or c < 0 or c >= N

    finished = [[False] * N for _ in range(N)]

    def bfs(r: int, c: int, visit_func):
        color = grid[r][c]
        queue = deque([(r, c)])

        visited = [[False] * N for _ in range(N)]
        visited[r][c] = True

        while queue:
            r, c = queue.popleft()
            visit_func(r, c)

            for k in range(4):
                nr = r + delta[k]
                nc = c + delta[3 - k]

                if is_invalid(nr, nc) or visited[nr][nc]:
                    continue
                if grid[nr][nc] != RAINBOW and grid[nr][nc] != color:
                    continue

                visited[nr][nc] = True
                finished[nr][nc] = True
                queue.append((nr, nc))

    score = 0
    while True:
        finished = [[False] * N for _ in range(N)]

        max_block = (0, 0)
        max_total_count = 1
        max_rainbow_count = 0

        for r in range(N):
            for c in range(N):
                if finished[r][c] or grid[r][c] <= 0:
                    continue

                get_total_count, get_rainbow_count, count = counter()
                bfs(r, c, count)

                if (get_total_count(), get_rainbow_count()) < (
                    max_total_count,
                    max_rainbow_count,
                ):
                    continue

                max_block = (r, c)
                max_total_count = get_total_count()
                max_rainbow_count = get_rainbow_count()

        if max_total_count == 1:
            break

        score += max_total_count**2

        bfs(*max_block, empty)

        pull_down_grid()
        rotate_grid()
        pull_down_grid()

    print(score)


main()
