from collections import deque

N, L, R = map(int, input().split())

pop = [list(map(int, input().split())) for _ in range(N)]
unionPop = []
unionCnt = []
unionNum = [[-1] * N for _ in range(N)]


def bfs(start: tuple[int, int]):
    queue = deque([start])

    r, c = start

    unionNum[r][c] = len(unionPop)
    unionPop.append(pop[r][c])
    unionCnt.append(1)

    while queue:
        r, c = queue.popleft()

        delta = (1, -1, 0, 0)
        for k in range(4):
            nr = r + delta[k]
            nc = c + delta[3 - k]

            if (
                0 <= nr < N
                and 0 <= nc < N
                and unionNum[nr][nc] == -1
                and L <= abs(pop[r][c] - pop[nr][nc]) <= R
            ):
                unionNum[nr][nc] = len(unionPop) - 1
                unionPop[-1] += pop[nr][nc]
                unionCnt[-1] += 1
                queue.append((nr, nc))


ans = 0
while True:
    unionPop.clear()
    unionCnt.clear()
    unionNum = [[-1] * N for _ in range(N)]

    for i in range(N):
        for j in range(N):
            if unionNum[i][j] == -1:
                bfs((i, j))

    for i in range(N):
        for j in range(N):
            k = unionNum[i][j]
            pop[i][j] = unionPop[k] // unionCnt[k]

    if len(unionPop) == N * N:
        break
    ans += 1

print(ans)
