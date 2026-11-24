k, n = map(int, input().split())
lines = [int(input()) for _ in range(k)]

small = 1
big = max(lines)
mid = big

def getNumberOfLines(length: int, lines: list[int]) -> int:
    res = 0
    for line in lines:
        res += line // length
    return res

beforeNumberOfLines = 0

while small != mid:
    numberOfLines = getNumberOfLines(mid, lines)
    if numberOfLines < n:
        big = mid
    elif numberOfLines >= n:
        small = mid
    mid = (small + big) // 2

print(mid)