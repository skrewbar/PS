n, m, r = map(int, input().split())

item = list(map(int, input().split()))

dist = [[float("inf")] * n for _ in range(n)]
for i in range(n):
    dist[i][i] = 0

for _ in range(r):
    a, b, l = map(int, input().split())
    a -= 1
    b -= 1

    dist[a][b] = l
    dist[b][a] = l


for k in range(n):
    for i in range(n):
        for j in range(n):
            dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j])

max_item = 0
for i in range(n):
    item_count = 0
    for j in range(n):
        if dist[i][j] <= m:
            item_count += item[j]
    max_item = max(item_count, max_item)

print(max_item)
