from collections import deque
import sys

input = lambda: sys.stdin.readline().rstrip()

for _ in range(int(input())):
    n, pointer = map(int, input().split())
    queue = deque(list(map(int, input().split())))

    count = 1
    while queue:
        if max(queue) > queue[0]:
            queue.append(queue.popleft())
            if pointer == 0:
                pointer = len(queue) - 1
            else:
                pointer -= 1
        else:
            queue.popleft()
            if pointer == 0:
                break
            else:
                pointer -= 1
                count += 1
    print(count)
