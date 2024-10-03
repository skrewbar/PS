rightList: list = [1, 1, 2, 2, 2, 8]


def main() -> None:
    global rightList

    inputList: list = list(map(int, input().split()))
    for i in range(len(inputList)):
        print(rightList[i] - inputList[i], end=" ")


if __name__ == "__main__":
    main()
