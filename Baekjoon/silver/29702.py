from math import log2, floor
import sys

input = lambda: sys.stdin.readline().rstrip()

for i in range(int(input())):
    n = int(input())

    while n != 1:
        floor_ = floor(log2(n) + 1)
        hosu = n - 2 ** floor(log2(n)) + 1
        zeroCount = 18 - len(str(hosu))
        if zeroCount > 0:
            answer = str(floor_) + "0" * zeroCount + str(hosu)
        else:
            answer = str(floor_) + str(hosu)
        print(answer)

        n //= 2
    print(1_000_000_000_000_000_001)
