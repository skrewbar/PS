n = int(input())

entrants = []

for _ in range(n):
    info = input().split()

    if info[1] == "hewhak":
        continue
    if info[2] == "winner":
        continue
    if 1 <= int(info[3]) <= 3:
        continue

    entrants.append((int(info[4]), info[0]))

entrants.sort()
print(len(entrants[:10]))
for _, name in sorted(entrants[:10], key=lambda x: x[1]):
    print(name)
