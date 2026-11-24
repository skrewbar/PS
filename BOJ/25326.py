n, m = map(int, input().split())

serveys = []
for _ in range(n):
    serveys.append(tuple(input().split()))

for _ in range(m):
    query = tuple(input().split())
    ans = 0
    for s in serveys:
        matches = True
        for column in range(3):
            if query[column] == "-":
                continue
            if query[column] != s[column]:
                matches = False

        if matches:
            ans += 1

    print(ans)
