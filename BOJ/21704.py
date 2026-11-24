def main():
    n, k = map(int, input().split())
    m = int(input())

    ranges = sorted(tuple(map(int, input().split())) for _ in range(m))

    answer = 0

    while ranges:
        l, r = ranges.pop()

        if k < r - l + 1:
            count = (r - l) // k
            answer += (2 * r - (count - 1) * k) * count
            r -= count * k

        answer += 2 * r
        bukkit_remain = k - (r - l + 1)

        while ranges:
            l, r = ranges.pop()
            if bukkit_remain < (r - l + 1):
                r -= bukkit_remain
                ranges.append((l, r))
                break
            bukkit_remain -= r - l + 1

    print(answer)


main()
