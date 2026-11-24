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

    def rotatedCW(self):
        return Direction((self.idx + 1) % len(self.delta))

    def rotatedCCW(self):
        return Direction((self.idx - 1) % len(self.delta))


def main():
    N, T = map(int, input().split())

    d = Direction(0)  # right
    pos = (0, 0)

    prevTime = 0
    for _ in range(N):
        time, s = input().split()
        time = int(time)

        pos = (pos[0] + d.dx * (time - prevTime), pos[1] + d.dy * (time - prevTime))

        if s == "left":
            d = d.rotatedCCW()
        else:
            d = d.rotatedCW()

        prevTime = time

    pos = (pos[0] + d.dx * (T - prevTime), pos[1] + d.dy * (T - prevTime))
    print(*pos)


main()
