X, Y = map(int, input().split())

X = X - 1 + Y
X %= 12

print(X + 1)
