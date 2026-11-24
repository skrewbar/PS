cards = input()
dp = [[0, 0] for _ in range(len(cards))]

dp[0][False] = 1

for i in range(1, len(cards)):
    if cards[i] == "0":
        dp[i][True] = dp[i - 1][False]
        continue

    dp[i][False] = dp[i - 1][False] + dp[i - 1][True]
    if cards[i - 1] != "0" and int(cards[i - 1] + cards[i]) <= 34:
        dp[i][True] = dp[i - 1][False]

print(sum(dp[len(cards) - 1]))
