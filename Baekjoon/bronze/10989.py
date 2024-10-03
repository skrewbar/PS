import sys

N = int(sys.stdin.readline())
nums = [0 for i in range(10001)]

for i in range(N):
    nums[int(sys.stdin.readline())] += 1

for i in range(1, 10001):
    n = nums[i]
    for j in range(n):
        print(i)
