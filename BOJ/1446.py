INF = int(1e9)


def main():
    N, D = map(int, input().split())

    shortcuts = [list(map(int, input().split())) for _ in range(N)]
    shortcuts.sort(reverse=True)

    minDist = [INF] * (10001)
    minDist[0] = 0

    for i in range(0, D + 1):
        minDist[i] = min(minDist[i], minDist[i - 1] + 1)

        while shortcuts:
            s, e, d = shortcuts[-1]
            if s < i:
                shortcuts.pop()
            if s != i:
                break

            minDist[e] = min(minDist[e], minDist[s] + d)
            shortcuts.pop()

    print(minDist[D])


main()
