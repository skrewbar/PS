from collections import namedtuple

max_ = namedtuple("max_", ["x", "y", "value"])
m = max_(0, 0, 0)

for row in range(9):
    numbers = list(map(int, input().split()))
    for col in range(9):
        if numbers[col] > m.value:
            m = max_(row, col, numbers[col])

print(m.value)
print(m.x + 1, m.y + 1)
