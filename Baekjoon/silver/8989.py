import sys

input = lambda: sys.stdin.readline().rstrip()


def getAngle(time: str) -> tuple[float, int]:
    hour, minute = map(int, time.split(":"))
    hour %= 12
    hourDegree = hour * 30 + minute / 2
    minuteDegree = minute * 6
    degree = abs(hourDegree - minuteDegree)
    return (min(degree, 360 - degree), time)


for t in range(int(input())):
    print(sorted(input().split(), key=getAngle)[2])
