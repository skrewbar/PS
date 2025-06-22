for _ in range(int(input())):
    n, s = map(int, input().split())

    answer = 0

    for _ in range(n):
        dx, dy, x, y = map(int, input().split())

        if dx == 0 or dy == 0:
            continue

        if dx == dy and y == x:
            answer += 1
        elif y == s - x:
            answer += 1

    print(answer)
