import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())
people = [list(map(int, input().split())) for _ in range(n)]
grades = [1 for _ in range(n)]
for i in range(n):
    p, q = people[i]
    for j in range(n):
        x, y = people[j]
        if x > p and y > q:
            grades[i] += 1

print(*grades)