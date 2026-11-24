def solve():
    X, Y, x, y = map(int, input().split())

    canPlace = [[True] * Y for _ in range(X)]
    ans = 0

    for i in range(X):
        for j in range(Y):
            if not canPlace[i][j]:
                continue

            ans += 1
            if i + x < X and j + y < Y:
                canPlace[i + x][j + y] = False

    print(ans)


def main():
    T = int(input())

    for _ in range(T):
        solve()


main()
