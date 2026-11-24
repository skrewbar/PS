def lower_bound(arr, x):
    lo, hi = 0, len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] < x:
            lo = mid + 1
        else:
            hi = mid
    return lo


def upper_bound(arr, x):
    lo, hi = 0, len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        if arr[mid] <= x:
            lo = mid + 1
        else:
            hi = mid
    return lo


t = int(input())

n = int(input())
a = list(map(int, input().split()))
a_sum = []

for i in range(n):
    sum_ = 0
    for j in range(i, n):
        sum_ += a[j]
        a_sum.append(sum_)

a_sum.sort()


m = int(input())
b = list(map(int, input().split()))
answer = 0

for i in range(m):
    sum_ = 0
    for j in range(i, m):
        sum_ += b[j]
        answer += upper_bound(a_sum, t - sum_) - lower_bound(a_sum, t - sum_)

print(answer)
