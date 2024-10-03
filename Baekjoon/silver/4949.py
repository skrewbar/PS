def isCorrect(string: str) -> bool:
    openedList = []  # small = 0, big = 1
    openBracket = {"(", "["}
    mate = {")": "(", "]": "["}

    for char in string:
        if char in openBracket:
            openedList.append(char)
        elif char in mate:
            if not openedList:
                return False
            if openedList.pop() != mate[char]:
                return False
            
    if openedList:
        return False
    return True


string = input()
answerList = ["no", "yes"]
while string != ".":
    print(answerList[isCorrect(string)])
    string = input()
