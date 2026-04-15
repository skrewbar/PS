import heapq


def main():
    N = int(input())

    heap = []
    for _ in range(N):
        for num in map(int, input().split()):
            heapq.heappush(heap, num)

        while len(heap) > N:
            heapq.heappop(heap)

    print(heap[0])


main()
