for _ in range(int(input())):
    l1, b1, l2, b2, l3, b3 = map(int, input().split())

    square = False

    square |= l1 == l2 == l3 and l1 == b1 + b2 + b3
    square |= b1 == b2 == b3 and b1 == l1 + l2 + l3
    square |= l2 == l3 and b1 == b2 + b3 and l1 + l2 == b1
    square |= b2 == b3 and l1 == l2 + l3 and b1 + b2 == l1

    print("YES" if square else "NO")
