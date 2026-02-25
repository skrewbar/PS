INF = int(1e9)

COORD = [
    (3, 1),
    (0, 0),
]

for i in range(2, 10):
    row, col = COORD[i - 1]

    col += 1
    if col >= 3:
        row += 1
        col = 0

    COORD.append((row, col))


def get_effort(a: int, b: int) -> int:
    x_a, y_a = COORD[a]
    x_b, y_b = COORD[b]

    return abs(x_a - x_b) + abs(y_a - y_b)


def main():
    hour, minute = map(int, input().split(":"))

    answer = (hour, minute)
    answer_effort = INF

    for h in range(hour, 100, 24):
        for m in range(minute, 100, 60):
            effort_sum = get_effort(h // 10, h % 10)
            effort_sum += get_effort(h % 10, m // 10)
            effort_sum += get_effort(m // 10, m % 10)

            if effort_sum < answer_effort:
                answer = (h, m)
                answer_effort = effort_sum

    print(f"{answer[0]:0>2}:{answer[1]:0>2}")


main()
