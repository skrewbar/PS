from math import log2, floor


def main():
    n = int(input())

    if n == 0:
        print(1)
    elif n < 0:
        print(32)
    else:
        print(floor(log2(n)) + 1)


main()
