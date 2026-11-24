dr = [1, -1, 0, 0]
dc = [0, 0, 1, -1]


def main():
    N = int(input())

    def isInvalid(r: int, c: int) -> bool:
        return r < 0 or r >= N or c < 0 or c >= N

    stud_cnt = N * N

    prefer = [[] for _ in range(stud_cnt + 1)]
    numbers = []
    for _ in range(stud_cnt):
        i, *pref = map(int, input().split())
        numbers.append(i)
        prefer[i] = pref

    seat = [[0] * N for _ in range(N)]

    def get_empty_count(r: int, c: int) -> int:
        ret = 0

        for k in range(4):
            nr = r + dr[k]
            nc = c + dc[k]

            if isInvalid(nr, nc):
                continue

            ret += 1 if seat[nr][nc] == 0 else 0

        return ret

    def get_prefer_count(r: int, c: int, num: int) -> int:
        ret = 0

        for k in range(4):
            nr = r + dr[k]
            nc = c + dc[k]

            if isInvalid(nr, nc):
                continue

            ret += 1 if seat[nr][nc] in prefer[num] else 0

        return ret

    for i in numbers:
        s = (0, 0)
        empty_cnt = -1
        prefer_cnt = -1

        for r in range(N):
            for c in range(N):
                if seat[r][c] != 0:
                    continue

                p = get_prefer_count(r, c, i)
                e = get_empty_count(r, c)

                if p < prefer_cnt:
                    continue

                if prefer_cnt < p:
                    s = (r, c)
                    prefer_cnt = p
                    empty_cnt = e
                    continue

                if empty_cnt < e:
                    s = (r, c)
                    empty_cnt = e

        seat[s[0]][s[1]] = i

    ans = 0
    for r in range(N):
        for c in range(N):
            match get_prefer_count(r, c, seat[r][c]):
                case 0:
                    continue
                case 1:
                    ans += 1
                case 2:
                    ans += 10
                case 3:
                    ans += 100
                case 4:
                    ans += 1000

    print(ans)


main()
