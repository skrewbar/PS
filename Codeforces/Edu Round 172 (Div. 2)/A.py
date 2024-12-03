for t in range(int(input())):
    n, k = map(int, input().split())
    arr = sorted(map(int, input().split()), reverse=True)

    i = 0
    coin = 0
    while i < n and coin + arr[i] <= k:
        coin += arr[i]
        i += 1
    print(k - coin)
