import sys

input = lambda: sys.stdin.readline().rstrip()


def dist(p1, p2):
    dx = p1[0] - p2[0]
    dy = p1[1] - p2[1]

    return dx * dx + dy * dy


def main():
    N, X_A, Y_A, R = map(int, input().split())

    ans = 0
    for _ in range(N):
        X, Y, P = map(int, input().split())

        if dist((X_A, Y_A), (X, Y)) <= R * R:
            ans += P

    print(ans)


main()
