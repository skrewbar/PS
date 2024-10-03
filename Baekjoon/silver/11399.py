import sys

input = lambda: sys.stdin.readline().rstrip()

input()
p = sorted(map(int, input().split()))

for i in range(1, len(p)):
    p[i] = p[i - 1] + p[i]

print(sum(p))
