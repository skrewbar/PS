import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

delta = [1, -1, 0, 0]
direction = "DULR"

INF = int(5e6)


def main():
    H, W = map(int, input().split())
    S = [input() for _ in range(H)]

    def invalid(r, c):
        return r < 0 or r >= H or c < 0 or c >= W

    dest = (0, 0)
    start = (0, 0)
    for i in range(H):
        for j in range(W):
            if S[i][j] == "S":
                start = (i, j)
            elif S[i][j] == "G":
                dest = (i, j)

    time = [[[-1] * 4 for _ in range(W)] for _ in range(H)]
    prv = [[[(0,0)] * 4 for _ in range(W)] for _ in range(H)]

    time[start[0]][start[1]] = [0] * 4
    queue = deque([(start[0], start[1], -1)])
    while queue:
        r, c, d = queue.popleft()

        if time[r][c][d] > INF:
            continue

        if S[r][c] == "G":
            break

        for k in range(4):
            if S[r][c] == "x" and k == d:
                continue
            elif S[r][c] == "o" and k != d:
                continue

            nr = r + delta[k]
            nc = c + delta[3 - k]

            if invalid(nr, nc) or S[nr][nc] == "#":
                continue
            if time[nr][nc][k] != -1:
                continue

            time[nr][nc][k] = time[r][c][d] + 1
            prv[nr][nc][k] = (k, d)

            queue.append((nr, nc, k))

    d = -1
    for i in range(4):
        if time[dest[0]][dest[1]][i] != -1:
            d = i

    if d == -1:
        print("No")
        return

    ans = []
    r, c = dest
    while (r, c) != start:
        d, prvd = prv[r][c][d]
        ans.append(direction[d])

        r, c = r - delta[d], c - delta[3 - d]
        d = prvd

    print("Yes")
    print("".join(reversed(ans)))


main()
