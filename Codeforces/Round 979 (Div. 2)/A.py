for t in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))

    min_ = min(arr)
    max_ = max(arr)

    print((max_ - min_) * (n - 1))
