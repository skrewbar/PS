import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()

n, k = map(int, input().split())
queue = deque([i for i in range(1, n + 1)])
answerList = []
while queue:
    for i in range(k-1):
        queue.append(queue.popleft())
    answerList.append(queue.popleft())

print("<", end="")
print(*answerList, sep=", ", end="")
print(">")
