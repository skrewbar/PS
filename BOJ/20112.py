n = int(input())
magic_square = [input() for _ in range(n)]
ans = "YES"
for i in range(n):
    horizonal = magic_square[i]
    vertical = ""
    for j in range(n):
        vertical += magic_square[j][i]
    if horizonal != vertical:
        ans = "NO"
        break
print(ans)