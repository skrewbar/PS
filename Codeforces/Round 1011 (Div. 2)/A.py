for _ in range(int(input())):
    n, k = map(int, input().split())
    s = input()

    uni = False

    if s < s[::-1]:
        uni = True
    elif k > 0 and len(set(s)) >= 2:
        uni = True

    print("YES" if uni else "NO")
