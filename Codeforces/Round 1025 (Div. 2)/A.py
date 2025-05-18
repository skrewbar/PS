for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))

    cancel = False
    for i in range(n):
        if a[i] != 0:
            continue

        if (i > 0 and a[i - 1] == 0) or (i + 1 < n and a[i + 1] == 0):
            cancel = True
            break
    
    if 0 not in a:
        cancel = True

    print("YES" if cancel else "NO")
