from typing import cast


class Time:
    def __init__(self, h: int, m: int):
        self.h = h
        self.m = m

    @staticmethod
    def parseTime(time: str) -> "Time":
        if time == "-:-":
            return Time(0, 0)
        return Time(*map(int, time.split(":")))

    def __int__(self) -> int:
        return self.h * 60 + self.m

    def __str__(self) -> str:
        return f"{self.h:0>2}:{self.m:0>2}"

    def __add__(self, other: "int | Time") -> "Time":
        m = int(self) + int(other)

        isNegative = m < 0
        m = abs(m)

        h = m // 60
        m %= 60

        return Time(-h, -m) if isNegative else Time(h, m)

    def __sub__(self, other: "Time") -> "Time":
        return self + (-int(other))

    def getDuration(self, to: "Time") -> "Time":
        t = to - self

        if int(t) < 0:
            t += Time(24, 0)

        return t


dist = {
    "Seoul": 0,
    "Yeongdeungpo": 9.1,
    "Anyang": 23.9,
    "Suwon": 41.5,
    "Osan": 56.5,
    "Seojeongri": 66.5,
    "Pyeongtaek": 75.0,
    "Seonghwan": 84.4,
    "Cheonan": 96.6,
    "Sojeongni": 107.4,
    "Jeonui": 114.9,
    "Jochiwon": 129.3,
    "Bugang": 139.8,
    "Sintanjin": 151.9,
    "Daejeon": 166.3,
    "Okcheon": 182.5,
    "Iwon": 190.8,
    "Jitan": 196.4,
    "Simcheon": 200.8,
    "Gakgye": 204.6,
    "Yeongdong": 211.6,
    "Hwanggan": 226.2,
    "Chupungnyeong": 234.7,
    "Gimcheon": 253.8,
    "Gumi": 276.7,
    "Sagok": 281.3,
    "Yangmok": 289.5,
    "Waegwan": 296.0,
    "Sindong": 305.9,
    "Daegu": 323.1,
    "Dongdaegu": 326.3,
    "Gyeongsan": 338.6,
    "Namseonghyeon": 353.1,
    "Cheongdo": 361.8,
    "Sangdong": 372.2,
    "Miryang": 381.6,
    "Samnangjin": 394.1,
    "Wondong": 403.2,
    "Mulgeum": 412.4,
    "Hwamyeong": 421.8,
    "Gupo": 425.2,
    "Sasang": 430.3,
    "Busan": 441.7,
}


def main():
    N, Q = map(int, input().split())

    arrival: dict[str, Time] = {}
    departure: dict[str, Time] = {}

    for _ in range(N):
        name, arr, dep = input().split()

        arrival[name] = Time.parseTime(arr)
        departure[name] = Time.parseTime(dep)

    for _ in range(Q):
        start, end = input().split()

        t = departure[start].getDuration(arrival[end])

        print(abs(dist[end] - dist[start]) / int(t) * 60)


main()
