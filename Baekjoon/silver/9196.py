while True:
    h, w = map(int, input().split())
    if h == 0 and w == 0:
        break

    answer = (150, 150)

    for i in range(1, 151):
        for j in range(i + 1, 151):
            diag = i * i + j * j
            if diag < h * h + w * w:
                continue
            if diag == h * h + w * w and i <= h:
                continue

            if (diag < answer[0] ** 2 + answer[1] ** 2) or (
                diag == answer[0] ** 2 + answer[1] ** 2 and i < answer[0]
            ):
                answer = (i, j)

    print(*answer)
