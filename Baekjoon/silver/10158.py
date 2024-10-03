w, h = map(int, input().split())
p, q = map(int, input().split())
t = int(input())

x = (p + t) % w
if (p + t) // w % 2 == 1:
    x = w - x

y = (q + t) % h
if (q + t) // h % 2 == 1:
    y = h - y

print(x, y)
