for t in range(int(input())):
    s = input()

    important = True

    if len(s) <= 2:
        important = False

    elif s[0] + s[1] != "10":
        important = False

    elif s[2] == "0":
        important = False

    elif int(s[2:]) < 2:
        important = False

    print("YES") if important else print("NO")
