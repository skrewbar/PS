def square(a, x=2):  # a^x
    if x == 0:
        return 1
    if x == 1:
        return a
    else:
        root = square(a, x // 2)

        if x % 2 == 0:  # 지수가 짝수이면
            return root * root
        else:
            return root * root * a


case = sorted(list(map(int, input().split())))
while case != [0, 0, 0]:
    if square(case[2]) == (square(case[0]) + square(case[1])):
        print("right")
    else:
        print("wrong")
    case = sorted(list(map(int, input().split())))
