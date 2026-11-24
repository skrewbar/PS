T = int(input())
for case in range(T):
    H, W, N = map(int, input().split())
    if N % H == 0:
        num = N // H
        floor = H
    else:
        num = N // H + 1
        floor = N % H
    print(floor * 100 + num)
