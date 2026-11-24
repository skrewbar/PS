def main():
    N = int(input())
    M = int(input())

    actions = [tuple(map(int, input().split())) for _ in range(M)]
    actions.sort()

    cnt = 0
    end = 0
    for x, y in actions:
        if end < x:
            cnt += x - end
        end = max(end, y)

    cnt += N - end

    print(cnt)


main()
