N = int(input())

ans = [0] * 9
peopleCut = [4, 11, 23, 40, 60, 77, 89, 96, 101]

A = sorted(map(int, input().split()), reverse=True)

rank = 0
for i in range(N):
    ans[rank] += 1
    if i + 1 < N and A[i] == A[i + 1]:
        continue

    while i + 1 >= peopleCut[rank]:
        rank += 1

print(*ans, sep="\n")
