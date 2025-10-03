N = int(input())

stack = [0] + [int(input()) for _ in range(N)]
pos = [0] * (N + 1)
for i in range(1, N + 1):
    pos[stack[i]] = i

pull = [False] * (N + 1)
completed = [False] * (N + 1)
minCompletedIdx = N + 1

for i in range(N, 0, -1):
    if pull[i]:
        continue

    for j in range(pos[i] + 1, minCompletedIdx):
        pull[stack[j]] = True

        for k in range(stack[j] - 1, 0, -1):
            if pull[k]:
                break
            pull[k] = True

    minCompletedIdx = pos[i]

print(pull.count(True))
