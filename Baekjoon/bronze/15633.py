n = int(input())
answer = 0
for i in range(1, n + 1):
    if n % i == 0:
        answer += i

print(answer * 5 - 24)
