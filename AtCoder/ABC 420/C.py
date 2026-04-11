N, Q = map(int, input().split())

A = [0] + list(map(int, input().split()))
B = [0] + list(map(int, input().split()))

ans = 0
for i in range(1, N + 1):
    ans += min(A[i], B[i])

for _ in range(Q):
    c, X, V = input().split()
    X = int(X)
    V = int(V)

    if A[X] < B[X]:
        ans -= A[X]
    else:
        ans -= B[X]

    if c == "A":
        A[X] = V
    else:
        B[X] = V
    
    ans += min(A[X], B[X])

    print(ans)
