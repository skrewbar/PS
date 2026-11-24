n = int(input())
cakes = list(map(int, input().split()))

ans = 0

for select in range(1, 1 << n):
    sum_ = 0
    for i in range(n):
        if (select & (1 << i)):
            sum_ += 1/cakes[i]
    
    if (99/100 <= sum_ <= 101/100):
        ans += 1

print(ans)