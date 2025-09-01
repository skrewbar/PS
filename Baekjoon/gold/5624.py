N = int(input())
A = list(map(int, input().split()))

two: set[int] = set()

ans = 0

for i in range(N):
    for j in range(i):
        if A[i] - A[j] in two:
            ans += 1
            break

    two.add(A[i] << 1)
    for j in range(i):
        two.add(A[i] + A[j])

print(ans)
