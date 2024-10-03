import sys
from math import floor

input = lambda: sys.stdin.readline().rstrip()

n = int(input())
opinions = []
except_ = floor((n * 15 / 100)+0.5)
average = 0
for _ in range(n):
    opinions.append(int(input()))
opinions.sort()

for i in range(except_, n - except_):
    average += opinions[i]

if n == 0:
    print(0)
else:
