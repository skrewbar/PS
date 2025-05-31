for _ in range(int(input())):
    s = input()
    open = 1
    possible = False
    for i in range(1, len(s)):
        if s[i] == "(":
            open += 1
        else:
            open -= 1
        if open == 0 and i != len(s) - 1:
            possible = True
            break

    print("YES" if possible else "NO")
