import sys

input = lambda: sys.stdin.readline().rstrip()

cityCount = int(input())
busCount = int(input())

distance = [[float("inf") for _ in range(cityCount + 1)] for _ in range(cityCount + 1)]

for i in range(1, cityCount + 1):
    distance[i][i] = 0

for _ in range(busCount):
    from_, to, cost = map(int, input().split())
    distance[from_][to] = min(distance[from_][to], cost)

for k in range(1, cityCount + 1):
    for i in range(1, cityCount + 1):
        for j in range(1, cityCount + 1):
            distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j])

for i in range(1, cityCount + 1):
    for j in range(1, cityCount + 1):
        (
            print(distance[i][j], end=" ")
            if distance[i][j] != float("inf")
            else print(0, end=" ")
        )
    print()
