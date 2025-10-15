def gcd(a: int, b: int) -> int:
    while b:
        a, b = b, a % b
    return a


def main():
    ni, mj = map(int, input().split())

    image = [list(input()) for _ in range(ni)]

    j = 0
    consecutive = 1
    for c in range(1, mj):
        isSame = True
        for r in range(ni):
            if image[r][c] != image[r][c - 1]:
                isSame = False

        if isSame:
            consecutive += 1
        else:
            j = gcd(j, consecutive)
            consecutive = 1

    j = gcd(j, consecutive)

    i = 0
    consecutive = 1
    for r in range(1, ni):
        isSame = True
        for c in range(0, mj, j):
            if image[r][c] != image[r - 1][c]:
                isSame = False

        if isSame:
            consecutive += 1
        else:
            i = gcd(i, consecutive)
            consecutive = 1

    i = gcd(i, consecutive)

    print(ni // i, mj // j)
    for r in range(0, ni, i):
        for c in range(0, mj, j):
            print(image[r][c], end="")
        print()


main()
