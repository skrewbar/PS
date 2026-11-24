from collections import deque


def solve():
    N, M, K = map(int, input().split())

    village = [input() for _ in range(N)]

    def getAccidentCnt(i: int, j: int) -> int:
        c = ord(village[i][j])

        if ord("0") <= c <= ord("9"):
            return c - ord("0")
        return 0

    dist = [[[-1] * 4 for _ in range(M)] for _ in range(N)]
    queue: deque[tuple[int, int, int, int, int]] = deque()

    findHome = False
    for i in range(N):
        if findHome:
            break

        for j in range(M):
            if village[i][j] == "H":
                findHome = True
                dist[i][j][0] = 0
                queue.append((i, j, -1, -1, 0))

    while queue:
        i, j, pi, pj, p = queue.popleft()
        prevCnt = getAccidentCnt(pi, pj)

        if village[i][j] == "S":
            print(dist[i][j][p])
            return

        delta = [1, -1, 0, 0]
        for k in range(4):
            ni = i + delta[k]
            nj = j + delta[3 - k]

            if (ni, nj) == (pi, pj):
                continue

            if not (0 <= ni < N and 0 <= nj < M) or village[ni][nj] == "X":
                continue

            nowCnt = getAccidentCnt(i, j)
            nxtCnt = getAccidentCnt(ni, nj)

            if dist[ni][nj][k] != -1:
                continue

            if prevCnt + nowCnt + nxtCnt > K:
                continue

            dist[ni][nj][k] = dist[i][j][p] + 1
            queue.append((ni, nj, i, j, k))

    print(-1)


solve()
