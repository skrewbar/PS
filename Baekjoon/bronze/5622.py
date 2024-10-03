timeList: list = [i + 1 for i in range(10)]


def getNum(string: str) -> int:
    if string in "ABC":
        return 2
    elif string in "DEF":
        return 3
    elif string in "GHI":
        return 4
    elif string in "JKL":
        return 5
    elif string in "MNO":
        return 6
    elif string in "PQRS":
        return 7
    elif string in "TUV":
        return 8
    elif string in "WXYZ":
        return 9


def main():
    sum: int = 0

    for char in input():
        num = getNum(char)
        sum += timeList[num]
    print(sum)


if __name__ == "__main__":
    main()
