import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


T = int(input())

for i in range(T):
    p = input()
    n = int(input())
    list_ = input()

    array = deque()
    reverse = 0
    exec(f"array = deque({list_})")

    success = True
    for cmd in p:
        if cmd == "R":
            reverse = reverse ^ 1
        elif cmd == "D":
            if not array:
                print("error")
                success = False
                break
            if reverse:
                array.pop()
            else:
                array.popleft()

    if success:
        if reverse:
            print("[" + ",".join(map(str, reversed(array))) + "]")
        else:
            print("[" + ",".join(map(str, array)) + "]")
