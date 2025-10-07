from collections import deque

INF = 1 << 14

N, M = map(int, input().split())

lab = [list(map(int, input().split())) for _ in range(N)]

inactives = []
emptyCnt = 0
for i in range(N):
    for j in range(N):
        if lab[i][j] == 0:
            emptyCnt += 1
        elif lab[i][j] == 2:
            inactives.append((i, j))


def getSpreadTime(actives: list[tuple[int, int]]):
    remainEmpty = emptyCnt

    queue = deque(actives)
    time = [[-1] * N for _ in range(N)]
    for i, j in actives:
        time[i][j] = 0

    while queue:
        i, j = queue.popleft()

        delta = [1, -1, 0, 0]
        for k in range(4):
            ni = i + delta[k]
            nj = j + delta[3 - k]

            if (0 <= ni < N and 0 <= nj < N) and lab[i][j] != 1 and time[ni][nj] == -1:
                time[ni][nj] = time[i][j] + 1
                if lab[ni][nj] == 0:
                    remainEmpty -= 1
                    if remainEmpty == 0:
                        return time[ni][nj]
                queue.append((ni, nj))

    return -1


def backtrack(idx: int, actives: list[tuple[int, int]]) -> int:
    if len(actives) == M:
        return getSpreadTime(actives)

    minTime = INF
    for i in range(idx + 1, len(inactives)):
        actives.append(inactives[i])
        time = backtrack(i, actives)
        if time != -1:
            minTime = min(minTime, time)
        actives.pop()

    return minTime if minTime != INF else -1


print(backtrack(-1, []) if emptyCnt else 0)
