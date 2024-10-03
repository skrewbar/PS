import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())
cost = list(map(int, input().split()))

for i in range(1, n):
    nextCost = list(map(int, input().split()))
    nextCost[0] += min(cost[1], cost[2])
    nextCost[1] += min(cost[0], cost[2])
    nextCost[2] += min(cost[0], cost[1])
    cost = nextCost

print(min(cost))
