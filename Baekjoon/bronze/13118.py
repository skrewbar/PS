p = list(map(int, input().split()))
x, y, r = map(int, input().split())

isCollided = False
for i in range(4):
    if p[i] == x:
        print(i + 1)
        isCollided = True
        break

if not isCollided:
    print(0)
