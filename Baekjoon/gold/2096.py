import sys

input = lambda: sys.stdin.readline().rstrip()


n = int(input())
max_dp = [0] * 3
min_dp = [0] * 3


for i in range(n):
    a, b, c = map(int, input().split())

    temp = [0] * 3
    temp[0] = a + max(max_dp[:-1])
    temp[1] = b + max(max_dp)
    temp[2] = c + max(max_dp[1:])
    max_dp = list(temp)

    temp = [0] * 3
    temp[0] = a + min(min_dp[:-1])
    temp[1] = b + min(min_dp)
    temp[2] = c + min(min_dp[1:])
    min_dp = list(temp)


print(max(max_dp), min(min_dp))
# print(max_dp)
# print(min_dp)
