for _ in range(int(input())):
    n = int(input())
    arr = sorted(map(int, input().split()))

    answer = 0
    for i in range(n):
        if (arr[i] + arr[-1]) % 2 == 0:
            answer = i
            break
    
    for i in range(n):
        if (arr[0] + arr[n - 1 - i]) % 2 == 0:
            answer = min(answer, i)

    print(answer)