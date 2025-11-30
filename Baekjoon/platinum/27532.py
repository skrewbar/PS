def main():
    M = int(input())

    times: list[int] = []
    for _ in range(M):
        hour, minute = map(int, input().split(":"))
        hour %= 12
        times.append(hour * 60 + minute)

    ans = M
    for R in range(1, 720 + 1):
        initialTimes: set[int] = set()

        for i in range(M):
            initialTimes.add((times[i] - i * R) % 720)
        ans = min(ans, len(initialTimes))

    print(ans)


main()
