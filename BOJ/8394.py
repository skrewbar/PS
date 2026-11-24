i, j = 1, 1
for _ in range(int(input())):
    i, j = j % 10, i + j
print(i)
