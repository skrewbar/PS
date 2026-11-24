import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

meetings = []
for _ in range(int(input())):
    meetings.append(list(map(int, input().split())))
meetings.sort()

count = 0
lastEndTime = 0
for startTime, endTime in meetings:
    if lastEndTime <= startTime:
        count += 1
        lastEndTime = endTime
    lastEndTime = min(lastEndTime, endTime)

print(count)
