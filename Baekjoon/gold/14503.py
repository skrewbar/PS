class Direction:
    delta = [-1, 0, 1, 0]

    def __init__(self, value: int):
        self.value = value

    @property
    def dr(self):
        return self.delta[self.value]

    @property
    def dc(self):
        return self.delta[3 - self.value]

    def rotateCounterClock(self):
        self.value = (self.value - 1) % 4


UP, RIGHT, DOWN, LEFT = map(Direction, range(4))

N, M = map(int, input().split())
r, c, d = map(int, input().split())
d = Direction(d)

grid = [list(map(int, input().split())) for _ in range(N)]
clearedCnt = 0
while True:
    if grid[r][c] == 0:
        clearedCnt += 1
        grid[r][c] = 2

    notCleared = False
    for i in range(4):
        tempDir = Direction(i)
        nr = r + tempDir.dr
        nc = c + tempDir.dc

        if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] == 0:
            notCleared = True
            break

    if notCleared:
        d.rotateCounterClock()
        nr = r + d.dr
        nc = c + d.dc

        if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] == 0:
            r = nr
            c = nc
    else:
        nr = r - d.dr
        nc = c - d.dc

        if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != 1:
            r = nr
            c = nc
        else:
            break

print(clearedCnt)
