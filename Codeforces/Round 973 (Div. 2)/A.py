for t in range(int(input())):
    n = int(input())
    x, y = map(int, input().split())
    print(-(-n // min(x, y)))
