n = int(input())

warzone = [input().split() for _ in range(n)]
nouzen = None

for i in range(n):
    if nouzen is not None:
        break
    for j in range(n):
        if warzone[i][j] == "2":
            nouzen = (i, j)
            break

output = None

for i in range(n):
    if output is not None:
        break
    for j in range(n):
        if warzone[i][j] != "1":
            continue

        if abs(i - j) % 2 == abs(nouzen[0] - nouzen[1]) % 2:
            output = "Kiriya"
            break

if output is None:
    output = "Lena"

print(output)
