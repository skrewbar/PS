n = int(input())
nums = list(map(int, input().split()))

max_sum = list(nums)
for i in range(1, n):
    max_sum[i] = max(max_sum[i - 1] + nums[i], max_sum[i])

print(max(max_sum))
