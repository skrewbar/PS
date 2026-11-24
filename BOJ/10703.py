class Meteor:
    def __init__(self, pic: list[list[str]]):
        self.pic = pic
        self.r, self.c = len(pic), len(pic[0])
        self.surface = [None] * s
        self.grounds = set()
        self.fall_dist = 0

        for i in range(self.r - 1, -1, -1):
            for j in range(self.c):
                if self.surface[j] is None and self.pic[i][j] == "X":
                    self.surface[j] = i
                    self.pic[i][j] = "."
                elif pic[i][j] == "#":
                    self.grounds.add((i, j))

    def fall(self) -> bool:
        """
        유성을 한 픽셀 아래로 떨어뜨리고,
        만약 떨어뜨릴 수 없다면 False를 반환합니다.
        """

        new_surface = self.surface.copy()
        for j, i in enumerate(self.surface):
            if i is None:
                continue
            if (i + 1, j) in self.grounds:
                return False
            new_surface[j] = i + 1
        self.surface = new_surface
        self.fall_dist += 1
        return True

    def print(self) -> None:
        for i in range(self.r - 1, -1, -1):
            for j in range(self.c):
                if self.pic[i][j] == "X":
                    self.pic[i + self.fall_dist][j] = "X"
                    self.pic[i][j] = "."

        for j, i in enumerate(self.surface):
            if i is None:
                continue
            self.pic[i][j] = "X"

        for row in self.pic:
            print(*row, sep="")


r, s = map(int, input().split())

meteor = Meteor([list(input()) for _ in range(r)])
while meteor.fall():
    ...
meteor.print()
