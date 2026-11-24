n, k = map(int, input().split())

bag = [[0] * (k + 1) for _ in range(n + 1)]
stuff = [[0, 0]] + [list(map(int, input().split())) for _ in range(n)]

for i in range(1, n + 1):
    for bag_weigh in range(1, k + 1):
        weigh, value = stuff[i]

        if bag_weigh < weigh:
            bag[i][bag_weigh] = bag[i - 1][bag_weigh]
        else:
            bag[i][bag_weigh] = max(
                bag[i - 1][bag_weigh],
                bag[i - 1][bag_weigh - weigh] + value,
            )

print(bag[n][k])
