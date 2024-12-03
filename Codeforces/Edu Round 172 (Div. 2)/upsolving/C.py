for t in range(int(input())):
    n, k = map(int, input().split())
    s = input()

    bob = s.count("1")
    alice = len(s) - bob

    profit = [0] * n
    for i in range(n):
        if s[i] == "1":
            bob -= 1
        else:
            alice -= 1

        profit[i] = bob - alice
    profit.sort(reverse=True)

    diff = 0
    i = 0
    while i < n and diff < k:
        diff += profit[i]
        i += 1

    if diff < k:
        print(-1)
    else:
        print(i + 1)
