import sys

input = lambda: sys.stdin.readline().rstrip()

S = set()

for cmd in range(int(input())):
    cmd = input().split()
    if cmd[0] == "add":
        S.add(cmd[1])
    elif cmd[0] == "remove":
        if cmd[0] in S:
            S.remove(cmd[1])
    elif cmd[0] == "check":
        if cmd[1] in S:
            print(1)
        else:
            print(0)
    elif cmd[0] == "toggle":
        if cmd[1] in S:
            S.remove(cmd[1])
        else:
            S.add(cmd[1])
    elif cmd[0] == "all":
        S = {i for i in range(1, 21)}
    elif cmd[0] == "empty":
        S = set()
