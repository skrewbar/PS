def main():
    N, M = map(int, input().split())

    comp = [[0] * N for _ in range(N)]
    for _ in range(M):
        A, B = map(lambda x: int(x) - 1, input().split())

        if comp[A][B] == -1:
            print(-1)
            return

        comp[A][B] = 1
        comp[B][A] = -1

    for k in range(N):
        for i in range(N):
            for j in range(N):
                if comp[i][j] != 0 and (
                    comp[i][j] == comp[j][i]
                    or (comp[i][k] != 0 and comp[i][k] == comp[k][j] and (comp[i][k] != comp[i][j]))
                ):
                    print(-1)
                    return

                if comp[i][j] == 0 and comp[i][k] == comp[k][j]:
                    comp[i][j] = comp[i][k]
                    comp[j][i] = -comp[i][k]

    for i in range(N):
        lo, hi = 1, N
        for j in range(N):
            if comp[i][j] == 1:
                hi -= 1
            elif comp[i][j] == -1:
                lo += 1

        print(lo, hi)


main()
