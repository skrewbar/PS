m, n = map(int, input().split())

count = 0

while True:
    # go right
    count += 1  # turn right
    m -= 1
    if m == 1:
        break
    # go down
    count += 1  # turn right
    n -= 1
    if n == 1:
        break


print(count + 1)
