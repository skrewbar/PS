g, l = map(int, input().split())
m = g * l
max_divisor = 1


def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


for i in range(1, int(m ** (1 / 2)) + 1):
    if max_divisor < i and m % i == 0 and gcd(i, m // i) == g:
        max_divisor = i

print(max_divisor, m // max_divisor)
