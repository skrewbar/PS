class Direction:
    delta = [1, 0, -1, 0]

    def __init__(self, idx: int):
        self.idx = idx

    @property
    def dx(self):
        return self.delta[self.idx]

    @property
    def dy(self):
        return self.delta[3 - self.idx]

    def rotateCW(self):
        self.idx = (self.idx + 1) % 4


DOWN, LEFT, UP, RIGHT = map(lambda x: lambda: Direction(x), range(4))

N, M = map(int, input().split())

grid = [list(map(int, input().split())) for _ in range(N)]


class CCTV:
    def __init__(self, x: int, y: int, type: int):
        self.x = x
        self.y = y
        self.directions = [RIGHT()]

        if type == 2 or type == 4 or type == 5:
            self.directions.append(LEFT())
        if type >= 3:
            self.directions.append(UP())
        if type == 5:
            self.directions.append(DOWN())

    def rotateCW(self):
        for d in self.directions:
            d.rotateCW()

    def findBlindSpot(self, canWatch: list[list[bool]]):
        for d in self.directions:
            x, y = self.x, self.y

            while 0 <= x < N and 0 <= y < M and grid[x][y] != 6:
                canWatch[x][y] = True
                x += d.dx
                y += d.dy


wallCnt = 0
cctvs: list[CCTV] = []
for x in range(N):
    for y in range(M):
        if 1 <= grid[x][y] <= 5:
            cctvs.append(CCTV(x, y, grid[x][y]))
        if grid[x][y] == 6:
            wallCnt += 1


def getAnswer(i: int) -> int:
    if i == len(cctvs):
        canWatch = [[False] * M for _ in range(N)]
        for cctv in cctvs:
            cctv.findBlindSpot(canWatch)

        cnt = 0
        for x in range(N):
            for y in range(M):
                if not canWatch[x][y]:
                    cnt += 1

        return cnt

    ret = getAnswer(i + 1)
    for _ in range(3):
        cctvs[i].rotateCW()
        ret = min(ret, getAnswer(i + 1))

    return ret


print(getAnswer(0) - wallCnt)
