import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

dq = deque()
for _ in range(int(input())):
    cmd = input().split()

    if cmd[0] == "push_front":
        dq.appendleft(cmd[1])
    elif cmd[0] == "push_back":
        dq.append(cmd[1])
    elif cmd[0] == "pop_front":
        try:
            print(dq.popleft())
        except IndexError:
            print(-1)
    elif cmd[0] == "pop_back":
        try:
            print(dq.pop())
        except IndexError:
            print(-1)
    elif cmd[0] == "size":
        print(len(dq))
    elif cmd[0] == "empty":
        print(int(len(dq) == 0))
    elif cmd[0] == "front":
        try:
            print(dq[0])
        except IndexError:
            print(-1)
    elif cmd[0] == "back":
        try:
            print(dq[-1])
        except IndexError:
            print(-1)