def main():
    N, M, K = map(int, input().split())

    A = [list(map(int, input().split())) for _ in range(N)]

    ages = [[[] for _ in range(N)] for _ in range(N)]
    for _ in range(M):
        r, c, a = map(int, input().split())
        r -= 1
        c -= 1
        ages[r][c].append(a)

    nourishment = [[5] * N for _ in range(N)]

    for _ in range(K):
        # spring
        for i in range(N):
            for j in range(N):
                ages[i][j].sort()
                dead = -1
                for k in range(len(ages[i][j])):
                    if nourishment[i][j] >= ages[i][j][k]:
                        nourishment[i][j] -= ages[i][j][k]
                        ages[i][j][k] += 1
                    else:
                        dead = k
                        break

                # summer
                if dead >= 0:
                    for k in range(dead, len(ages[i][j])):
                        nourishment[i][j] += ages[i][j][k] // 2

                    del ages[i][j][dead:]

        # fall
        for i in range(N):
            for j in range(N):
                for k in range(len(ages[i][j])):
                    if ages[i][j][k] % 5 == 0:
                        di = [0, 1, 1, 1, 0, -1, -1, -1]
                        dj = [1, 1, 0, -1, -1, -1, 0, 1]
                        for l in range(8):
                            ni = i + di[l]
                            nj = j + dj[l]

                            if 0 <= ni < N and 0 <= nj < N:
                                ages[ni][nj].append(1)

        # winter
        for i in range(N):
            for j in range(N):
                nourishment[i][j] += A[i][j]

    ans = 0
    for i in range(N):
        for j in range(N):
            ans += len(ages[i][j])

    print(ans)


main()
