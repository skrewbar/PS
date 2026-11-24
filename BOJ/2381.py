n = int(input())
points = sorted(
    [list(map(int, input().split())) for _ in range(n)], key=lambda x: x[0] + x[1]
)
ans = abs(points[0][0] - points[-1][0]) + abs(points[0][1] - points[-1][1])
points.sort(key=lambda x: x[0] - x[1])
print(max(ans, abs(points[0][0] - points[-1][0]) + abs(points[0][1] - points[-1][1])))
