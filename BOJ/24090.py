n, k = map(int, input().split())
a = list(map(int, input().split()))


def swapped(a, b):
    global k
    
    if k == 1:
        print(b, a)
        exit()
    k -= 1

    return b, a


def partition(p, r):
    x = a[r]
    i = p - 1
    for j in range(p, r):
        if a[j] <= x:
            i += 1
            a[i], a[j] = swapped(a[i], a[j])
    if i + 1 != r:
        a[i + 1], a[r] = swapped(a[i + 1], a[r])
    return i + 1


def quick_sort(p, r):
    if p < r:
        q = partition(p, r)
        quick_sort(p, q - 1)
        quick_sort(q + 1, r)


quick_sort(0, n - 1)
print(-1)
