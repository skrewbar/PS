class Time:
    def __init__(self, time: str):
        self.h, self.m, self.s = map(int, time.split(":"))

    def add(self, sec: int):
        self.s += sec

        if self.s >= 60:
            self.m += self.s // 60
            self.s %= 60

        if self.m >= 60:
            self.h += self.m // 60
            self.m %= 60

        if self.h >= 24:
            self.h %= 24

    def __ne__(self, other: object) -> bool:
        if isinstance(other, Time):
            return self.h != other.h or self.m != other.m or self.s != other.s
        return True

    def __eq__(self, other: object) -> bool:
        return not self != other

    def isMultipleOf(self, num: int) -> bool:
        return (self.h * 10000 + self.m * 100 + self.s) % num == 0


def main():
    for _ in range(3):
        cnt = 0

        start, end = map(Time, input().split())
        end.add(1)

        if start == end:
            if start.isMultipleOf(3):
                cnt += 1
            start.add(1)

        while start != end:
            if start.isMultipleOf(3):
                cnt += 1

            start.add(1)

        print(cnt)


main()
