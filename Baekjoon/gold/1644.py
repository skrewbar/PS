n = int(input())

is_prime = [True] * (n+1)
prime_numbers = []

for i in range(2, n+1):
    if is_prime[i]:
        prime_numbers.append(i)
        for j in range(2 * i, n+1, i):
            is_prime[j] = False

l, r = 0, 0
sum_ = 0
ans = 0
while r < len(prime_numbers):
    sum_ += prime_numbers[r]
    while n < sum_:
        sum_ -= prime_numbers[l]
        l += 1

    if sum_ == n:
        ans += 1
    r += 1

print(ans)
