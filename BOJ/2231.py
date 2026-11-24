n = int(input())

exists = False

for i in range(1, n):
    if i + sum(list(map(int, list(str(i))))) == n:
        print(i)
        exists = True
        break

if not exists:
    print(0)