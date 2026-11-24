import heapq, sys

input = lambda: sys.stdin.readline().rstrip()

heap = []

N = int(input())
for i in range(N):
    x = int(input())
    if x == 0:  # x가 0이면
        if heap:  # heap에 원소가 있으면
            print(-heapq.heappop(heap))
        else:
            print(0)
    else:  # x가 0이 아니면
        heapq.heappush(heap, -x)
