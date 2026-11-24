def getTawla(num: int):
    if num == 1:
        return "Yakk"
    elif num == 2:
        return "Doh"
    elif num == 3:
        return "Seh"
    elif num == 4:
        return "Ghar"
    elif num == 5:
        return "Bang"
    elif num == 6:
        return "Sheesh"


def getAnswer(numList: list[int]) -> str:
    num1, num2 = sorted(numList, reverse=True)
    if num1 == num2: #같은 수가 나오는 경우
        if num1 == 1:
            return "Habb Yakk"
        elif num1 == 2:
            return "Dobara"
        elif num1 == 3:
            return "Dousa"
        elif num1 == 4:
            return "Dorgy"
        elif num1 == 5:
            return "Dabash"
        elif num1 == 6:
            return "Dosh"
    elif num1 + num2 == 11:
        return "Sheesh Beesh"
    else:
        return getTawla(num1) + " " + getTawla(num2)



def main() -> None:
    t = int(input())
    for caseNum in range(1, t + 1):
        num1, num2 = map(int, input().split())
        print(f"Case {caseNum}: " + getAnswer([num1, num2]))


if __name__ == "__main__":
    main()