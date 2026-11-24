n = int(input())
players = list(map(int, input().split()))
playerSet = set(players)
maxNum = max(players)
score = [0 for _ in range(maxNum + 1)]

for i in players:
    for j in range(i, maxNum + 1, i):
        if j in playerSet:
            score[i] += 1
            score[j] -= 1

for i in players:
    print(score[i], end=" ")
