import sys

input = lambda: sys.stdin.readline().rstrip()

for _ in range(int(input())):
    count = 0
    divisor = 5
    n = int(input())
    while n // divisor != 0:
        count += n // divisor
        divisor *= 5
    print(count)
