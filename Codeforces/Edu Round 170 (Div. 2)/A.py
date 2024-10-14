for t in range(int(input())):
    s = input()
    t = input()

    LCPIndex = 0  # longest common prefix index

    for i in range(min(len(s), len(t))):
        if s[i] != t[i]:
            break
        LCPIndex = i

    print(len(s) + len(t) - LCPIndex)
