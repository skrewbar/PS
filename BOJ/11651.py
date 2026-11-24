dots = []

for _ in range(int(input())):
    dots.append(list(map(int, input().split())))

dots.sort(key=lambda x: (x[1], x[0]))

for i in dots:
    print(*i)
