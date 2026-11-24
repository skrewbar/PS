n, k = map(int, input().split())
a = list(map(int, input().split()))
tmp = [0] * n


def merge_sort(p, r):
    if p < r:
        q = (p + r) // 2
        merge_sort(p, q)
        merge_sort(q + 1, r)
        merge(p, q, r)


def save(i, t):
    global k

    if k == 1:
        print(tmp[t])
        exit()
    k -= 1
    a[i] = tmp[t]


def merge(p, q, r):
    i, j, t = p, q + 1, 0
    while i <= q and j <= r:
        if a[i] <= a[j]:
            tmp[t] = a[i]
            t += 1
            i += 1
        else:
            tmp[t] = a[j]
            t += 1
            j += 1

    while i <= q:
        tmp[t] = a[i]
        t += 1
        i += 1
    while j <= r:
        tmp[t] = a[j]
        t += 1
        j += 1
    i = p
    t = 0
    while i <= r:
        save(i, t)
        i += 1
        t += 1

merge_sort(0, n-1)
print(-1)