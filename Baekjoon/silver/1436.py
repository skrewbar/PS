n = int(input())

movieCount = 0
i = 666
while movieCount != n:
    temp = i
    while temp != 0:
        if temp % 1000 == 666:
            movieCount += 1
            break
        else:
            temp //= 10
    i += 1

print(i - 1)