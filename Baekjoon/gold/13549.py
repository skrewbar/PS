import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


n, k = map(int, input().split())


def bfs(start: int, end: int) -> int:
    second = [0 for i in range(10_0001)]
    queue = deque([start])
    while len(queue) > 0:
        current = queue.popleft()
        if current == end:
            return second[current]

        for nxt in [current - 1, current + 1, current * 2]:
            if 0 <= nxt < 10_0001:
                if second[nxt] == 0:
                    if nxt == current * 2 and nxt != 0:
                        second[nxt] = second[current]
                        queue.appendleft(nxt)
                    else:
                        second[nxt] = second[current] + 1
                        queue.append(nxt)


print(bfs(n, k))
