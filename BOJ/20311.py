def main():
    N, K = map(int, input().split())
    c = sorted([count, i + 1] for i, count in enumerate(map(int, input().split())))

    if c[-1][0] > (N + 1) // 2:
        print(-1)
        return

    answer = [0] * N
    for i in range(0, N, 2):
        answer[i] = c[-1][1]
        c[-1][0] -= 1
        if c[-1][0] == 0:
            c.pop()

    for i in range(N):
        if answer[i] != 0:
            continue

        answer[i] = c[-1][1]
        c[-1][0] -= 1
        if c[-1][0] == 0:
            c.pop()
    
    print(*answer)


main()
