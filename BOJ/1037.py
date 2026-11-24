count = int(input())
divisors = list(map(int, input().split()))
print(min(divisors) * max(divisors))
