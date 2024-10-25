def solve(x1: int, y1: int, r1: int, x2: int, y2: int, r2: int):
    dist = (x1 - x2) ** 2 + (y1 - y2) ** 2

    if dist == 0:
        print(-1 if r1 == r2 else 0)
        return

    if dist == (r1 + r2) ** 2:
        print(1)
        return

    if dist > (r1 + r2) ** 2:
        print(0)
        return

    if dist == (r1 - r2) ** 2:
        print(1)
        return

    if dist < (r1 - r2) ** 2:
        print(0)
        return

    print(2)


for t in range(int(input())):
    solve(*map(int, input().split()))
