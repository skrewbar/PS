n = int(input())
n -= 1

i = 1
while 0 < n:
    n -= 6 * i
    i += 1

if n == 0:
    print(2)
else:
    print(i)
