for t in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))

    bn = 0
    for i in arr:
        bn += 1
        if bn == i:
            bn += 1

    print(bn)
