import heapq


def heappush(heap: list[tuple[int, int]], item: tuple[int, int]):
    i, b_i = item
    heapq.heappush(heap, (-b_i, i))


def heappop(heap: list[tuple[int, int]]):
    b_i, i = heapq.heappop(heap)
    return (i, -b_i)


def main():
    N, M = map(int, input().split())

    subjects: list[tuple[int, int]] = []

    a = list(map(int, input().split()))
    for i, b_i in enumerate(map(int, input().split())):
        heappush(subjects, (i, b_i))

    remain = 24 * N
    while remain and subjects:
        i, b_i = heappop(subjects)

        study_time = min(remain, (100 - a[i]) // b_i)
        remain -= study_time
        a[i] += study_time * b_i

        if a[i] < 100:
            b_i = 100 - a[i]
            heappush(subjects, (i, b_i))

    print(sum(a))


main()
