WOMAN = 0
MAN = 1


def charToGender(c: str):
    if c == "W":
        return WOMAN
    else:
        return MAN


def solve():
    X = int(input())
    line = list(map(charToGender, input()))

    count = [0, 0]

    i = 0
    while i < len(line):
        now = line[i]
        i += 1

        while i < len(line) and count[line[i]] < count[line[i] ^ 1]:
            count[line[i]] += 1
            i += 1

        count[now] += 1

        if abs(count[0] - count[1]) > X:
            i -= 1
            break

    print(i)


solve()
