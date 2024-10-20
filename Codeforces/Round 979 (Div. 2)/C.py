for t in range(int(input())):
    n = int(input())
    s = input()
    if s[0] == "1" or s[-1] == "1" or s.count("11"):
        print("YES")
    else:
        print("NO")
