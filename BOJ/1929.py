m, n = map(int, input().split())

isPrime = [True for _ in range(n + 1)]
isPrime[1] = False

for i in range(2, int(n**(1/2))+1):
    if isPrime[i]:
        j = 2
        while i * j <= n:
            isPrime[i*j] = False
            j += 1

for i in range(m, n+1):
    if isPrime[i]:
        print(i)