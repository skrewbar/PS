for t in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))

    print(sum(arr) - arr[n - 2] * 2)
