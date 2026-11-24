N, L = map(int, input().split())

height = [list(map(int, input().split())) for _ in range(N)]


def canPassThrough(r: int, c: int, dr: int, dc: int) -> bool:
    flatCnt = 1

    for _ in range(N - 1):
        nr = r + dr
        nc = c + dc

        if not (0 <= nr < N and 0 <= nc < N):
            return True

        if height[r][c] - 1 == height[nr][nc]:
            r, c = nr, nc
            passable = True

            for _ in range(L - 1):
                nr += dr
                nc += dc

                if not (0 <= nr < N and 0 <= nc < N) or height[r][c] != height[nr][nc]:
                    passable = False
                    break

            if not passable:
                return False
            flatCnt = 0

        elif height[r][c] + 1 == height[nr][nc]:
            if flatCnt < L:
                return False
            flatCnt = 1
        elif height[r][c] == height[nr][nc]:
            flatCnt += 1
        else:
            return False

        r, c = nr, nc

    return True


ans = 0
for r in range(N):
    if canPassThrough(r, 0, 0, 1):
        ans += 1

for c in range(N):
    if canPassThrough(0, c, 1, 0):
        ans += 1

print(ans)
