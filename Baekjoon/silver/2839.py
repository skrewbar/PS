n = int(input())
five = n // 5

while True:
    if five < 0:
        print(-1)
        break
    elif (n - 5 * five) % 3 == 0:
        print((n - 5 * five) // 3 + five)
        break
    five -= 1
