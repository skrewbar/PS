for t in range(int(input())):
    n = int(input())
    occupied = [False for _ in range(n + 2)]
    order = list(map(int, input().split()))
    occupied[order[0]] = True

    followed = True
    for i in order[1:]:
        if not (occupied[i - 1] or occupied[i + 1]):
            followed = False
            break
        occupied[i] = True

    print("YES") if followed else print("NO")
