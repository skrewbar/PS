import sys

input = lambda: sys.stdin.readline().rstrip()

k = int(input())
numList = []
for i in range(k):
    int_ = int(input())
    if int_ == 0:
        numList.pop()
    else:
        numList.append(int_)

print(sum(numList))