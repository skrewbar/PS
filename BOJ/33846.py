n, t = map(int, input().split())
a = list(map(int, input().split()))

a[:t] = sorted(a[:t])
print(*a)
