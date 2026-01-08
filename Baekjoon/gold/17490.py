def main():
    N, M, K = map(int, input().split())

    if M <= 1:
        print("YES")
        return

    S = list(map(int, input().split()))

    passable = [True] * N

    for _ in range(M):
        i, j = map(lambda x: int(x) - 1, input().split())
        if i > j:
            i, j = j, i

        if i == 0 and j == N - 1:
            passable[N - 1] = False
        else:
            passable[i] = False

    start = 0
    while passable[(start - 1) % N]:
        start = (start - 1) % N

    minStone = S[start]
    i = (start + 1) % N
    while i != start:
        if not passable[(i - 1) % N]:
            K -= minStone
            minStone = S[i]

        minStone = min(minStone, S[i])

        i = (i + 1) % N
    K -= minStone

    if K < 0:
        print("NO")
        return

    print("YES")


main()
