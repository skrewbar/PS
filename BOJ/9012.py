T = int(input())


def isVPS(string: str) -> bool:
    opened = 0
    closed = 0
    for char in string:
        if opened < closed:
            return False
        if char == "(":
            opened += 1
        else:
            closed += 1
    if opened == closed:
        return True
    else:
        return False


for case in range(T):
    string = input()

    if isVPS(string):
        print("YES")
    else:
        print("NO")
