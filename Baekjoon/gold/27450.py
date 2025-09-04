from collections import deque

N, K = map(int, input().split())
p = list(map(int, input().split()))
t = list(map(int, input().split()))

answer = 0
lines: deque[tuple[int, int]] = deque()  # (index, count)
remainVolume = 0
remainCnt = 0

for i in range(N):
    remainVolume -= remainCnt
    p[i] += remainVolume

    lineCnt = max(0, (t[i] - p[i] + K - 1) // K)
    answer += lineCnt
    remainVolume += K * lineCnt
    remainCnt += lineCnt
    lines.append((i, lineCnt))

    while lines and lines[0][0] <= i - K:
        remainCnt -= lines[0][1]
        lines.popleft()

print(answer)
