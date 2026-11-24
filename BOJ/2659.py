def get_clock_num(num_list: list[int]) -> int:
    num = "".join(map(str, num_list))
    return int(
        min(
            num,
            num[1:] + num[:1],
            num[2:] + num[:2],
            num[3:] + num[:3],
        )
    )


clock_numbers = []

for a in range(1, 10):
    for b in range(1, 10):
        for c in range(1, 10):
            for d in range(1, 10):
                clock_numbers.append(get_clock_num((a, b, c, d)))


numbers = "".join(input().split())
clock_num = int(
    min(
        numbers,
        numbers[1:] + numbers[:1],
        numbers[2:] + numbers[:2],
        numbers[3:] + numbers[:3],
    )
)


def bisect_right(arr: list, x):
    lo, hi = 0, len(arr)

    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] <= x:
            lo = mid + 1
        else:
            hi = mid

    return lo


clock_numbers = sorted(set(clock_numbers))
print(bisect_right(clock_numbers, clock_num))
