N, K = map(int, input().split())

coins = [int(input()) for i in range(N)][::-1]
answer = 0

for coin in coins:
    answer += K // coin
    K %= coin
print(answer)
