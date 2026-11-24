from collections import deque
import sys

input = lambda: sys.stdin.readline().rstrip()


def get_max_doc(building: list[list[str]], keys: set[str]):
    ans = 0

    h = len(building)
    w = len(building[0])

    starts: list[tuple[int, int]] = []
    for i in (0, h - 1):
        for j in range(w):
            starts.append((i, j))
    for i in range(1, h - 1):
        for j in (0, w - 1):
            starts.append((i, j))

    while True:
        last_key_size = len(keys)

        queue = deque(starts)
        visited = [[False] * w for _ in range(h)]
        for i, j in starts:
            visited[i][j] = True
        while queue:
            i, j = queue.popleft()
            
            cur = building[i][j]
            if cur.isupper() and cur not in keys:
                continue
            if cur == "*":
                continue
            
            if cur.islower():
                keys.add(cur.upper())
            if cur == "$":
                ans += 1
                
            building[i][j] = "."

            for k in range(4):
                ni = i + [1, -1, 0, 0][k]
                nj = j + [0, 0, 1, -1][k]

                if 0 <= ni < h and 0 <= nj < w and not visited[ni][nj]:
                    visited[ni][nj] = True
                    queue.append((ni, nj))

        if last_key_size == len(keys):
            break
    return ans


for _ in range(int(input())):
    h, w = map(int, input().split())
    building = [list(input()) for _ in range(h)]
    keys = set()
    for key in input():
        keys.add(key.upper())

    print(get_max_doc(building, keys))
