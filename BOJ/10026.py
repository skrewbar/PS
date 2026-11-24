import sys, copy

sys.setrecursionlimit(10**6)

input = lambda: sys.stdin.readline().rstrip()


def dfs(x: int, y: int, color: str, grid: list[list[int]], blinded: bool) -> None:
    if blinded and color in {"R", "G"} and grid[x][y] in {"R", "G"}:
        grid[x][y] = "0"
    elif grid[x][y] == color:
        grid[x][y] = "0"
    else:
        return

    if 0 < x:
        dfs(x - 1, y, color, grid, blinded)
    if 0 < y:
        dfs(x, y - 1, color, grid, blinded)
    if x + 1 < len(grid):
        dfs(x + 1, y, color, grid, blinded)
    if y + 1 < len(grid):
        dfs(x, y + 1, color, grid, blinded)


n = int(input())

nonBlindGrid = [list(input()) for _ in range(n)]
nonBlindCount = 0

blindGrid = copy.deepcopy(nonBlindGrid)
blindCount = 0

for x in range(n):
    for y in range(n):
        if nonBlindGrid[x][y] != "0":
            dfs(x, y, nonBlindGrid[x][y], nonBlindGrid, False)
            nonBlindCount += 1

for x in range(n):
    for y in range(n):
        if blindGrid[x][y] != "0":
            dfs(x, y, blindGrid[x][y], blindGrid, True)
            blindCount += 1

print(nonBlindCount, blindCount)
