import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


for t in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    stack: deque[tuple[int, int]] = deque()

    for i in arr:
        sum_, cnt = i, 1

        while stack and stack[-1][0] >= sum_ // cnt:
            sum_ += stack[-1][0] * stack[-1][1]
            cnt += stack[-1][1]
            stack.pop()

        stack.append((sum_ // cnt, cnt - sum_ % cnt))
        if sum_ % cnt != 0:
            stack.append((sum_ // cnt + 1, sum_ % cnt))

    print(stack[-1][0] - stack[0][0])
