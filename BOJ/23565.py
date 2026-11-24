import sys

input = lambda: sys.stdin.readline().rstrip()

T = int(input())

for i in range(T):
    a, b, c, d = map(int, input().split())
    if a >= 2:
        if (b + c == 0) and (a < 4):
            print((a + 1) * (d + 1))
        else:
            print(a + 2 * b + 3 * c + 4 * d + 1)
    elif b >= 2:
        b += 2 * d
        if a == 1:
            print(a + 2 * b + 3 * c + 1)
        elif c >= 1:
            print(2 * b + 3 * c - 1)
        else:
            print(b + 1)

    else:
        if (a == 1) and (b == 1) and (c >= 1) and (d >= 1):  # 모두 양수면
            print(a + 2 * b + 3 * c + 4 * d + 1)
        elif (
            ((a + b + c == 0) and (d >= 1))
            or ((a + c + d == 0) and (b == 1))
            or ((a + b + d == 0) and (c >= 1))
            or ((b + c + d == 0) and (a == 1))  # 하나만 양수면
        ):
            print(a + b + c + d + 1)

        elif (a == 1) and (b == 1) and (c + d == 0):  # a==1, b==1
            print(4)
        elif (a == 1) and (c >= 1) and (b + d == 0):  # a==1, c만 양수면
            print((a + 1) * (c + 1))
        elif (a == 1) and (d >= 1) and (b + c == 0):  # a==1, d만 양수면
            print((a + 1) * (d + 1))
        elif (b == 1) and (c >= 1) and (a + d == 0):  # b==1, c만 양수면
            print((b + 1) * (c + 1))
        elif (b == 1) and (d >= 1) and (a + c == 0):  # b==1, d만 양수면
            print((b + 1) * (d + 1))
        elif (c >= 1) and (d >= 1) and (a + b == 0):  # c, d만 양수면
            if c == 1:
                print(2 + d * 2)
            elif c == 2:
                print(3 + d * 3)
            elif d == 1:
                print(3 * c + 4 * d - c - 2)
            else:
                print(3 * c + 4 * d - 5)

        elif (a == 0) and (b and c and d):  # a만 0이면
            print(3 * c + 4 * d + 1)
        elif (b == 0) and (a and c and d):  # b만 0이면
            if c == 1:
                print(1 + 3 * c + 3 * d)
            else:
                print(3 * c + 4 * d)
        elif (c == 0) and (a and b and d):  # c만 0이면
            print(4 * d + 4)
        elif (d == 0) and (a and b and c):  # d만 0이면
            print(3 * c + 4)
        else:
            print(1)


# 푸는데 5시간 50분걸렸다...
