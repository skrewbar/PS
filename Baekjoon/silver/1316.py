def main() -> None:
    count: int = 0
    n: int = int(input())

    for _ in range(n):
        word = input()
        usedCharList: list[str] = []
        for i in range(len(word)):
            if not word[i] in usedCharList:
                usedCharList.append(word[i])
            elif (word[i] in usedCharList) & (not word[i] == word[i-1]):
                count -= 1
                break
        count += 1
    print(count)
        



if __name__ == "__main__":
    main()
