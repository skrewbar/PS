number = input()[::-1]

dp = [0 for _ in range(len(number))]
prev = [None for _ in range(len(number))]

if number[0] == number[1]:
    dp[1] += 2
if 3 <= len(number):
    numset = set(number[:3])
    if len(numset) == 1:
        dp[2] += 2
    elif len(numset) == 2:
        dp[2] += 1
if 4 <= len(number):
    dp[3] = dp[1]
    if number[2] == number[3]:
        dp[3] += 2
    prev[3] = 1


for i in range(4, len(number)):
    two = dp[i - 2]
    numset = set((number[i], number[i - 1]))
    if len(numset) == 1:
        two += 2

    three = dp[i - 3]
    numset.add(number[i - 2])
    if len(numset) == 1:
        three += 2
    elif len(numset) == 2:
        three += 1

    prev[i] = i - 2 if three <= two else i - 3
    dp[i] = max(two, three)


ans = ""
i = len(number) - 1
while i > 2:
    ans += number[i : prev[i] : -1] + "-"
    i = prev[i]
print(ans + number[i::-1])
