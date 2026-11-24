def itol(n: int) -> list[int]:
    ret = []
    while n:
        ret.append(n % 10)
        n //= 10

    return ret[::-1]


def ltoi(lst: list[int]) -> int:
    ret = 0

    for i in lst:
        ret = 10 * ret + i

    return ret


def main():
    K, C = map(int, input().split())
    list_K = itol(K)

    prefsuf = 0

    for i in range(1, len(list_K)):
        if list_K[:i] == list_K[-i:]:
            prefsuf = i

    length = (len(list_K) - prefsuf) * K + prefsuf
    answer = 0

    for i in range(1, len(list_K) - prefsuf):
        pattern = list_K[:i]

        int_s = 0
        for j in range(len(list_K)):
            int_s = 10 * int_s + pattern[j % len(pattern)]

        if int_s <= K:
            pattern = itol(ltoi(pattern) + 1)

            if len(pattern) > i:
                continue

            int_s = 0
            for j in range(len(list_K)):
                int_s = 10 * int_s + pattern[j % len(pattern)]

        letter = i * int_s + (len(list_K) - i)
        answer = max(answer, length - letter - C * (int_s - K))

    print(answer)


main()
