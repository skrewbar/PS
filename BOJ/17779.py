def solve():
    N = int(input())
    A = [list(map(int, input().split())) for _ in range(N)]

    allSum = sum(map(sum, A))
    ans = 100 * N * N

    for x in range(N):
        for y in range(N):
            for d1 in range(1, y + 1):
                for d2 in range(1, min(N - y, N - x - d1)):
                    max_pop = 0
                    min_pop = allSum

                    pop5 = allSum

                    # 1번 선거구
                    pop = 0
                    for r in range(x + d1):
                        for c in range(y + 1):
                            if r + c < x + y:
                                pop += A[r][c]
                                pop5 -= A[r][c]
                    max_pop = max(max_pop, pop)
                    min_pop = min(min_pop, pop)

                    # 2번 선거구
                    pop = 0
                    for r in range(x + d2 + 1):
                        for c in range(y + 1, N):
                            if c - r > y - x:
                                pop += A[r][c]
                                pop5 -= A[r][c]
                    max_pop = max(max_pop, pop)
                    min_pop = min(min_pop, pop)

                    # 3번 선거구
                    pop = 0
                    for r in range(x + d1, N):
                        for c in range(y - d1 + d2):
                            if c - r < y - x - 2 * d1:
                                pop += A[r][c]
                                pop5 -= A[r][c]
                    max_pop = max(max_pop, pop)
                    min_pop = min(min_pop, pop)

                    # 4번 선거구
                    pop = 0
                    for r in range(x + d2 + 1, N):
                        for c in range(y - d1 + d2, N):
                            if r + c > x + y + 2 * d2:
                                pop += A[r][c]
                                pop5 -= A[r][c]

                    max_pop = max(max_pop, pop, pop5)
                    min_pop = min(min_pop, pop, pop5)

                    ans = min(ans, max_pop - min_pop)

    print(ans)


solve()
