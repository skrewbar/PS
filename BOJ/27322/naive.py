n = int(input())
arr = list(map(int, input().split()))


def range_min(l, r, x):
    for i in range(l, r + 1):
        arr[i] = min(x, arr[i])


def range_max(l, r, x):
    for i in range(l, r + 1):
        arr[i] = max(x, arr[i])


def range_add(l, r, x):
    for i in range(l, r + 1):
        arr[i] += x


m = int(input())
for _ in range(m):
    q, *info = map(int, input().split())
    info[0] -= 1
    info[1] -= 1
    if q == 1:
        range_min(*info)
    elif q == 2:
        range_max(*info)
    elif q == 3:
        range_add(*info)
    elif q == 4:
        print(min(arr[info[0]:info[1]+1]))
    elif q == 5:
        print(max(arr[info[0]:info[1]+1]))
    elif q == 6:
        print(sum(arr[info[0]:info[1]+1]))