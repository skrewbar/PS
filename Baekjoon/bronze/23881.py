N, K = map(int, input().split())
A = list(map(int, input().split()))

ans = ()
for i in range(N - 1, 0, -1):
    m = 0
    for j in range(i + 1):
        if A[j] > A[m]:
            m = j

    if m != i:
        A[i], A[m] = A[m], A[i]
        K -= 1

        if K == 0:
            ans = (A[m], A[i])
            break

if K:
    print(-1)
else:
    print(*ans)
