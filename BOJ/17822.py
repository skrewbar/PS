from collections import deque
from typing import cast

CLOCKWISE = 0
COUNTERCLOCKWISE = 1


def solve():
    N, M, T = map(int, input().split())
    disks: list[list[int | None]] = [list(map(int, input().split())) for _ in range(N)]

    def rotate(disk: list[int | None], clockwise: bool) -> None:
        """
        dist[i] represents the i-th number on the disk.
        Numbers are ordered in clockwise direction.

        The 1st number is on the right side of the disk.
        So the 2nd number is on the bottom side of the disk.
        """

        if clockwise:
            for i in range(M - 1, 0, -1):
                disk[i], disk[i - 1] = disk[i - 1], disk[i]
        else:
            for i in range(M - 1):
                disk[i], disk[i + 1] = disk[i + 1], disk[i]

    for _ in range(T):
        x, d, k = map(int, input().split())

        for i in range(x - 1, N, x):
            for _ in range(k):
                rotate(disks[i], d == CLOCKWISE)

        visited = [[False] * M for _ in range(N)]
        erased = False
        for i in range(N):
            for j in range(M):
                if visited[i][j] or disks[i][j] is None:
                    continue

                visited[i][j] = True

                queue = deque([(i, j)])
                number = disks[i][j]
                erasedCnt = 0

                while queue:
                    r, c = queue.popleft()
                    erasedCnt += 1

                    delta = [1, -1, 0, 0]
                    for k in range(4):
                        nr = r + delta[k]
                        nc = (c + delta[3 - k]) % M

                        if 0 <= nr < N and disks[nr][nc] == number:
                            visited[nr][nc] = True
                            disks[nr][nc] = None
                            queue.append((nr, nc))

                if erasedCnt == 1:
                    disks[i][j] = number
                else:
                    erased = True

        if not erased:
            total = 0
            cnt = 0

            for i in range(N):
                for j in range(M):
                    if disks[i][j] is None:
                        continue

                    total += cast(int, disks[i][j])
                    cnt += 1

            for i in range(N):
                for j in range(M):
                    number = disks[i][j]

                    if number is None:
                        continue

                    if number * cnt > total:
                        disks[i][j] = number - 1
                    elif number * cnt < total:
                        disks[i][j] = number + 1

    total = 0
    for i in range(N):
        for j in range(M):
            number = disks[i][j]

            if number is not None:
                total += number

    print(total)


solve()
