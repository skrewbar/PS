import sys
from heapq import *

input = lambda: sys.stdin.readline().rstrip()
probList: list[tuple[int, int]] = []

n = int(input())
probList = sorted([tuple(map(int, input().split())) for _ in range(n)])

queue = []
cupRamenSum = 0
for curTime in range(n, 0, -1):
    while probList and probList[-1][0] >= curTime:
        deadline, cupRamen = probList.pop()
        heappush(queue, -cupRamen)

    if queue:
        cupRamenSum += -heappop(queue)

print(cupRamenSum)
