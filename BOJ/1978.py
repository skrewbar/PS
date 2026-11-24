def isPrime(n: int) -> bool:
    if n == 1:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

N = int(input())
answer = 0
for n in map(int, input().split()):
    if isPrime(n):
        answer += 1
print(answer)
