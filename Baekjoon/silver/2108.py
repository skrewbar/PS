n = int(input())
nums = sorted([int(input()) for _ in range(n)])

print(round(sum(nums) / n))
print(nums[n // 2])

counts = {i: 0 for i in nums}
for i in nums:
    counts[i] += 1

modes = {nums[0]}
mode = nums[0]
for i in nums:
    if counts[i] > counts[mode]:
        mode = i
        modes = {mode}
    elif counts[i] == counts[mode]:
        modes.add(i)

if len(modes) > 1:
    print(sorted(modes)[1])
else:
    print(mode)

print(abs(max(nums) - min(nums)))