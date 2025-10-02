N, M = map(int, input().split())

for _ in range(M):
    a = list(map(int, input().split()))

    if N == 1:
        print(a[0])
        continue

    neg = sorted(filter(lambda x: x < 0, a))
    pos = list(filter(lambda x: x > 0, a))

    if len(neg) < 2 and not pos:
        print(0)
        continue

    ans = 1
    for i in range(0, len(neg) - 1, 2):
        ans *= neg[i] * neg[i + 1]
    
    for i in pos:
        ans *= i
    
    print(ans)
