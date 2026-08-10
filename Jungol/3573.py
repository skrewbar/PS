import sys

input = lambda: sys.stdin.readline().rstrip()

prior = {
    "(": -1,
    ")": -1,
    "+": 0,
    "-": 0,
    "*": 1,
    "/": 1,
}


def main():
    expr = input()

    oper_stk: list[str] = []

    for i in range(len(expr)):
        c = expr[i]
        if c not in prior:
            print(c, end="")
            continue

        if c == "(":
            oper_stk.append(c)
            continue

        while oper_stk and prior[oper_stk[-1]] >= prior[c]:
            top = oper_stk.pop()
            if top != "(":
                print(top, end="")

        if c != ")":
            oper_stk.append(c)

    print(*oper_stk, sep="")


main()
