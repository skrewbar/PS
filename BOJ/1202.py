import sys
from heapq import *

input = lambda: sys.stdin.readline().rstrip()


n, k = map(int, input().split())
gems = sorted([list(map(int, input().split())) for _ in range(n)], reverse=True)
capacities = sorted([int(input()) for _ in range(k)])

queue = []
sum_ = 0

for capacity in capacities:
    while len(gems) > 0 and gems[-1][0] <= capacity:
        m, v = gems.pop()
        heappush(queue, -v)

    if len(queue) > 0:
        sum_ += -heappop(queue)

print(sum_)
