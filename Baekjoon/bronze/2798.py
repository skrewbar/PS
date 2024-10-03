from itertools import combinations

N, M = map(int, input().split())
cards = list(map(int, input().split()))
cases = combinations(cards, 3)

answer = 0
for case in cases:
    sum_ = sum(case)
    if sum_ <= M:
        answer = max(answer, sum_)
print(answer)
