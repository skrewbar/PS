for t in range(int(input())):
    h, w = map(int, input().split())
    for _ in range(h):
        print(input()[::-1])
