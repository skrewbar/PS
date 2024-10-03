N = int(input())


def isPrime(num):
    for i in range(2, int(num ** (1 / 2))):
        if num % i == 0:
            return False
    return True


if N == 1:
    num = 2
else:
    num = N

while True:
    if isPrime(num) and (str(num) == str(num)[::-1]):
        print(num)
        break
    else:
        num += 1
