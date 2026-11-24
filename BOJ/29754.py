import sys

input = lambda: sys.stdin.readline().rstrip()


n, m = map(int, input().split())

info = {}
not_real = set()

for name, day, start, end in sorted(
    [input().split() for _ in range(n)], key=lambda x: int(x[1])
):
    start = tuple(map(int, start.split(":")))
    end = tuple(map(int, end.split(":")))
    day = int(day)

    if name in not_real:
        continue

    if name not in info:
        info[name] = {"last": 1, "count": 0, "total": 0}

    if (info[name]["last"] - 1) // 7 != (day - 1) // 7:  # 다음주로 넘어옴
        if info[name]["count"] < 5 or info[name]["total"] < 60 * 60:
            not_real.add(name)
            continue

        info[name]["count"] = 0
        info[name]["total"] = 0

    info[name]["count"] += 1
    info[name]["total"] += (end[0] - start[0]) * 60 + (end[1] - start[1])
    info[name]["last"] = day

for name in info:
    if (
        (info[name]["last"] - 1) // 7 != (m - 1) // 7
        or info[name]["count"] < 5
        or info[name]["total"] < 60 * 60
    ):
        not_real.add(name)

real = sorted(filter(lambda x: x not in not_real, info.keys()))

print(*real if real else [-1], sep="\n")
