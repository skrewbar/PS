import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


queue = deque()
n = int(input())
for _ in range(n):
    cmd = input().split()
    if cmd[0] == "push":
        queue.append(cmd[1])
    elif cmd[0] == "pop":
        if len(queue) > 0:
            print(queue.popleft())
        else:
            print(-1)
    elif cmd[0] == "size":
        print(len(queue))
    elif cmd[0] == "empty":
        if len(queue) == 0:
            print(1)
        else:
            print(0)
    elif cmd[0] == "front":
        if len(queue) > 0:
            print(queue[0])
        else:
            print(-1)
    elif cmd[0] == "back":
        if len(queue) > 0:
            print(queue[-1])
        else:
            print(-1)
