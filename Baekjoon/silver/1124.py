A, B = map(int, input().split())
is_prime = [True for _ in range(B + 1)]
is_prime[1] = False

m = int(B**0.5)
for n in range(2, m + 1):
    if is_prime[n]:
        for k in range(n, B + 1):
            if n * k > B:
                break
            is_prime[n * k] = False
    if n * (n + 1) > B:
        break

factor_counts = [0 for _ in range(B + 1)]

for i in range(1, B + 1):
    if is_prime[i]:
        factor_counts[i] = 1
for i in range(2, B + 1):
    for j in range(2, B + 1):
        if i * j > B:
            break
        if is_prime[j]:
            factor_counts[i * j] = factor_counts[i] + 1

answer = 0
for i in range(A, B + 1):
    if is_prime[factor_counts[i]]:
        answer += 1
print(answer)
