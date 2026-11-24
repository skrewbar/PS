nums = list(map(int, input().split()))
sum_ = 0
for n in nums:
    sum_ += n**2

print(sum_ % 10)
