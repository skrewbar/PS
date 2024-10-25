for t in range(int(input())):
    a, b = map(int, input().split())

    if a >= b:
        print(a)
        continue

    a -= b - a

    print(max(a, 0))
