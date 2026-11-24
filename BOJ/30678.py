import sys

sys.setrecursionlimit(10**9)

pattern = [
    [False, False, True, False, False],
    [False, False, True, False, False],
    [True, True, True, True, True],
    [False, True, True, True, False],
    [False, True, False, True, False],
]


def pow(base: int, exp: int) -> int:
    if exp == 0:
        return 1

    x = pow(base, exp // 2)

    if exp % 2 == 1:
        return x * x * base
    else:
        return x * x


def isStar(x: int, y: int, i: int) -> bool:
    if i == -1:
        return True
    
    nx = (x // pow(5, i)) % 5
    ny = (y // pow(5, i)) % 5
    
    if i == 0:
        return pattern[nx][ny]
    if pattern[nx][ny]:
        return isStar(x, y, i - 1)
    return False


n = int(input())

for i in range(pow(5, n)):
    for j in range(pow(5, n)):
        if isStar(i, j, n-1):
            print("*", end="")
        else:
            print(" ", end="")
    print()
