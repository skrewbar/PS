import heapq, sys

input = lambda: sys.stdin.readline().rstrip()

heap = []
N = int(input())
for i in range(N):
    x = int(input())
    if x == 0:  # x가 0이면
        if not heap:  # 배열이 비어 있으면
            print(0)
        else:
            print(heapq.heappop(heap)[1])
    else:  # x가 0이 아니면
        heapq.heappush(heap, (abs(x), x))
