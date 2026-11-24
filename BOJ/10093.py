A, B = sorted(map(int, input().split()))
print(max(0, B - A - 1))
print(*range(A + 1, B))
