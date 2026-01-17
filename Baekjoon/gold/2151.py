from collections import deque


def main():
    N = int(input())

    def isValid(r: int, c: int):
        return 0 <= r < N and 0 <= c < N

    grid = [input() for _ in range(N)]

    queue = deque()

    for i in range(N):
        for j in range(N):
            if grid[i][j] == "#":
                queue.append((i, j))

    while len(queue) > 1:
        queue.pop()

    dist = [[-1] * N for _ in range(N)]
    start = queue[0]
    dist[start[0]][start[1]] = 0

    while queue:
        r, c = queue.popleft()

        if (r, c) != start and grid[r][c] == "#":
            print(dist[r][c] - 1)
            return

        def search(r: int, c: int, dr: int, dc: int):
            nr, nc = r + dr, c + dc
            while isValid(nr, nc):
                if grid[nr][nc] == "*":
                    break
                if dist[nr][nc] == -1 and grid[nr][nc] != ".":
                    dist[nr][nc] = dist[r][c] + 1
                    queue.append((nr, nc))

                nr, nc = nr + dr, nc + dc

        search(r, c, 1, 0)
        search(r, c, -1, 0)
        search(r, c, 0, 1)
        search(r, c, 0, -1)


main()
