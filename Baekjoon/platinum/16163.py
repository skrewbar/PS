def manacher(string: str) -> list[int]:
    a = [0] * len(string)
    c = 0
    r = 0

    for i in range(len(string)):
        if r < i:
            a[i] = 0
        else:
            a[i] = min(r - i, a[(2 * c) - i])

        while (
            (0 <= i - a[i] - 1)
            and (i + a[i] + 1 < len(string))
            and (string[i - a[i] - 1] == string[i + a[i] + 1])
        ):
            a[i] += 1

        if r < i + a[i]:
            r = i + a[i]
            c = i
    return a


def main():
    string = "#" + "#".join(input()) + "#"
    answer = (len(string) - 1) // 2
    for v in manacher(string):
        answer += v // 2
    print(answer)


if __name__ == "__main__":
    main()
