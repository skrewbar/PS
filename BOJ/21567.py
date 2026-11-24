from collections import Counter

A, B, C = (int(input()) for _ in range(3))
counter = Counter(str(A * B * C))

for i in range(10):
    cnt = counter.get(str(i))
    print(cnt if cnt else 0)
