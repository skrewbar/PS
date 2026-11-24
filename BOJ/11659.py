import sys

input = lambda: sys.stdin.readline().rstrip()

N, M = map(int, input().split())
nums = list(map(int, input().split()))
sums = [0]  # Sn

for i in range(N):
    sums.append(sums[-1] + nums[i])


def getSum(i: int, j: int) -> int:  # i, j: Natural number
    return sums[j] - sums[i - 1]


for i in range(M):
    i, j = map(int, input().split())
    print(getSum(i, j))
