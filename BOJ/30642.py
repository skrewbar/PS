def solve():
    N = int(input())
    mascot = input()
    K = int(input())

    ans = 0
    if mascot == "annyong":
        if K & 1:
            ans = K
        else:
            ans = K - 1
    else:
        if ~K & 1:
            ans = K
        elif K == 1:
            ans = 2
        else:
            ans = K - 1

    print(ans)


solve()
