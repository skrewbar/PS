N = int(input())
stops = list(map(int, input().split()))[::-1]

current_vel = 1
sum_ = current_vel

for i in range(1, N):
    if stops[i] <= current_vel:
        current_vel = stops[i]
    else:
        current_vel += 1
    sum_ += current_vel
print(sum_)
