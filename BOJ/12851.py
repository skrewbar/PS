import sys
from collections import deque

input = lambda: sys.stdin.readline().rstrip()


n, k = map(int, input().split())


def bfs(start: int, end: int) -> int:
    min_second, ways = 0, 0
    second = [0 for i in range(10_0001)]
    queue = deque([start])
    while queue:
        current = queue.popleft()
        if current == end:
            min_second = second[current]
            ways += 1
            continue

        for nxt in [current + 1, current - 1, current * 2]:
            if 0 <= nxt < 10_0001:
                if second[nxt] == 0 or second[nxt] == second[current] + 1:
                    second[nxt] = second[current] + 1
                    queue.append(nxt)

    return [min_second, ways]


print(*bfs(n, k), sep="\n")
