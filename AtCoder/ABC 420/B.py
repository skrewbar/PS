N, M = map(int, input().split())

score = [0] * N

votes = [input() for _ in range(N)]

for i in range(M):
    x, y = 0, 0

    for p in range(N):
        if votes[p][i] == "0":
            x += 1
        else:
            y += 1

    if x == 0 or y == 0:
        for p in range(N):
            score[p] += 1
        continue

    for p in range(N):
        if x < y and votes[p][i] == "0":
            score[p] += 1
        elif x > y and votes[p][i] == "1":
            score[p] += 1

maxScore = 0
answer = []

for i in range(N):
    if score[i] > maxScore:
        maxScore = score[i]
        answer = [i + 1]
    elif score[i] == maxScore:
        answer.append(i + 1)

print(*answer)
