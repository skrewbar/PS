def gcd(a: int, b: int) -> int:
    while b:
        a, b = b, a % b

    return a


def main():
    n = int(input())
    g = 0

    for i in map(int, input().split()):
        g = gcd(g, i)

    for d in range(1, g + 1):
        if g % d == 0:
            print(d)


main()
