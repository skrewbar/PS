import heapq

N = int(input())
cards = [int(input()) for i in range(N)]
heapq.heapify(cards)

sum_ = 0
for i in range(len(cards) - 1):
    previous = heapq.heappop(cards)
    current = heapq.heappop(cards)
    sum_ += previous + current
    heapq.heappush(cards, previous + current)

print(sum_)
