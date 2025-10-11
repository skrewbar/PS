from collections import deque


def solve():
    N, M = map(int, input().split())

    queue: deque[tuple[int, int]] = deque()

    for i in range(N):
        line = input()
        for j in range(M):
            if line[j] == "o":
                queue.append((i, j))

    K = int(input())
    time = [[-1] * (M + 2 * K) for _ in range(N + 2 * K)]

    for i, j in queue:
        time[i][j] = 0

    ans = 0
    while queue:
        i, j = queue.popleft()
        ans += 1

        if time[i][j] == K:
            continue

        delta = [1, -1, 0, 0]
        for k in range(4):
            ni = i + delta[k]
            nj = j + delta[3 - k]

            if time[ni][nj] != -1:
                continue

            time[ni][nj] = time[i][j] + 1
            queue.append((ni, nj))

    print(ans)


solve()
