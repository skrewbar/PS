import sys

input = lambda: sys.stdin.readline().rstrip()
mu = [0 for i in range(44722)]


def setup() -> None:
    mu[1] = 1
    for i in range(1, 44722):
        for j in range(2 * i, 44722, i):
            mu[j] -= mu[i]


def get_SFI_count(k: int) -> int:
    count = 0
    i = 1
    while i * i <= k:
        count += mu[i] * (k // (i * i))
        i += 1
    return count


def get_SFI(search: int, start: int, end: int) -> int:
    mid = (start + end) // 2
    sfi_count = get_SFI_count(mid)

    if sfi_count == search:
        mid -= 1
        while get_SFI_count(mid) == search:
            mid -= 1
        return mid + 1
    elif sfi_count > search:
        return get_SFI(search, start, mid - 1)
    else:
        return get_SFI(search, mid + 1, end)


k = int(input())
setup()
print(get_SFI(k, k, k * 2))
