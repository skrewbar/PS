from typing import NamedTuple

dr = [-1, -1, 0, 1, 1, 1, 0, -1]
dc = [0, 1, 1, 1, 0, -1, -1, -1]

UNDETERMINED = -1
DIFFERENT = -2


class Fireball(NamedTuple):
    r: int
    c: int
    m: int
    s: int
    d: int


def main():
    N, M, K = map(int, input().split())

    fireballs: list[Fireball] = []

    for _ in range(M):
        r, c, m, s, d = map(int, input().split())
        fireballs.append(Fireball(r - 1, c - 1, m, s, d))

    for _ in range(K):
        mass = [[0] * N for _ in range(N)]
        speed = [[0] * N for _ in range(N)]
        direction = [[0] * N for _ in range(N)]
        cnt = [[0] * N for _ in range(N)]
        parity = [[UNDETERMINED] * N for _ in range(N)]

        for r, c, m, s, d in fireballs:
            r += dr[d] * s
            c += dc[d] * s

            r %= N
            c %= N

            mass[r][c] += m
            speed[r][c] += s
            direction[r][c] = d
            cnt[r][c] += 1

            if parity[r][c] == UNDETERMINED:
                parity[r][c] = d & 1
            if parity[r][c] != d & 1:
                parity[r][c] = DIFFERENT

        fireballs.clear()

        for r in range(N):
            for c in range(N):
                if cnt[r][c] == 1:
                    fireballs.append(Fireball(r, c, mass[r][c], speed[r][c], direction[r][c]))
                    continue

                m = mass[r][c] // 5
                if m == 0:
                    continue

                s = speed[r][c] // cnt[r][c]

                d = int(parity[r][c] == DIFFERENT)
                for _ in range(4):
                    fireballs.append(Fireball(r, c, m, s, d))
                    d += 2
    
    print(sum(map(lambda x: x.m, fireballs)))


main()
