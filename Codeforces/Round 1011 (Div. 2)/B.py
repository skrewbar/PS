for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))

    operations = []
    mid = n // 2

    if 0 in arr[mid:]:
        operations.append((mid + 1, n))
        n = mid + 1
    if 0 in arr[:mid]:
        operations.append((1, mid))
        n -= mid - 1
    operations.append((1, n))

    print(len(operations))
    for oper in operations:
        print(*oper)
