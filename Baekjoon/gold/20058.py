from collections import deque


def swap(arr: list[list[int]], a: tuple[int, int], b: tuple[int, int]) -> None:
    i, j = a
    k, l = b

    arr[i][j], arr[k][l] = arr[k][l], arr[i][j]


def main() -> None:
    N, Q = map(int, input().split())
    size = 1 << N
    A = [list(map(int, input().split())) for _ in range(size)]
    L = list(map(int, input().split()))

    def spin(leftup: tuple[int, int], rightdown: tuple[int, int]):
        lo_r, lo_c = leftup
        hi_r, hi_c = rightdown

        while lo_r < hi_r:
            size = hi_r - lo_r + 1

            for step in range(size - 1):
                swap(A, (lo_r, lo_c + step), (hi_r - step, lo_c))
                swap(A, (hi_r - step, lo_c), (hi_r, hi_c - step))
                swap(A, (hi_r, hi_c - step), (lo_r + step, hi_c))

            lo_r += 1
            lo_c += 1
            hi_r -= 1
            hi_c -= 1

    def divide_and_spin(leftup: tuple[int, int], size: int, level: int) -> None:
        r, c = leftup

        if size == 2**level:
            spin(leftup, (r + size - 1, c + size - 1))
            return

        size //= 2

        divide_and_spin((r, c), size, level)
        divide_and_spin((r, c + size), size, level)
        divide_and_spin((r + size, c), size, level)
        divide_and_spin((r + size, c + size), size, level)

    # cast firestorm
    delta = [1, -1, 0, 0]
    for level in L:
        divide_and_spin((0, 0), size, level)

        adjCnt = [[0] * size for _ in range(size)]
        for r in range(size):
            for c in range(size):
                if A[r][c] == 0:
                    continue

                for k in range(4):
                    nr = r + delta[k]
                    nc = c + delta[3 - k]

                    if nr < 0 or nr >= size or nc < 0 or nc >= size:
                        continue

                    if A[nr][nc]:
                        adjCnt[r][c] += 1
        for r in range(size):
            for c in range(size):
                if A[r][c] and adjCnt[r][c] <= 2:
                    A[r][c] -= 1

    # find answers
    summation = 0
    for i in range(size):
        summation += sum(A[i])

    maxCnt = 0

    visited = [[False] * size for _ in range(size)]
    for i in range(size):
        for j in range(size):
            if visited[i][j] or A[i][j] == 0:
                continue

            visited[i][j] = True

            cnt = 1
            queue = deque([(i, j)])
            while queue:
                r, c = queue.popleft()

                for k in range(4):
                    nr = r + delta[k]
                    nc = c + delta[3 - k]

                    if nr < 0 or nr >= size or nc < 0 or nc >= size:
                        continue
                    if visited[nr][nc] or A[nr][nc] == 0:
                        continue

                    visited[nr][nc] = True
                    cnt += 1
                    queue.append((nr, nc))

            maxCnt = max(maxCnt, cnt)

    print(summation)
    print(maxCnt)


main()
