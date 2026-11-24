import sys

input = lambda: sys.stdin.readline().rstrip()

stack = []

N = int(input())

for i in range(N):
    cmd = input()
    if "push" in cmd:
        stack.append(str(cmd.split()[1]))
    if cmd == "pop":
        if len(stack) == 0:
            print(-1)
        else:
            print(stack.pop())
    if cmd == "size":
        print(len(stack))
    if cmd == "empty":
        if len(stack) == 0:
            print(1)
        else:
            print(0)
    if cmd == "top":
        if len(stack) == 0:
            print(-1)
        else:
            print(stack[-1])
