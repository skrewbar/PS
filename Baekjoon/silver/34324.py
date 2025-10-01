target = "KUMOH"
revTarget = target[::-1]

N = int(input())
grid = [input() for _ in range(N)]

ans = 0

for i in range(N):
    chars = []
    for k in range(i + 1):
        if k >= len(grid[i - k]):
            continue

        chars.append(grid[i - k][k])

    s = "".join(chars)
    ans += max(s.count(target), s.count(revTarget))

for j in range(1, 1000):
    chars = []
    for k in range(N):
        if j + k >= len(grid[N - 1 - k]):
            continue

        chars.append(grid[N - 1 - k][j + k])

    s = "".join(chars)
    ans += max(s.count(target), s.count(revTarget))

print(ans)
