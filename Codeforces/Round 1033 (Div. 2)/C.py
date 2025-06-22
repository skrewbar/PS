def max_divine_of_root(n: int, x: int) -> int:
    return (n - x + 1) * x + (x - 1) * x // 2


def solve():
    n, m = map(int, input().split())

    if n > m or n * (n + 1) // 2 < m:
        print(-1)
        return

    root = 0
    child_cnt = n
    divine = 0

    for i in range(1, n + 1):
        root += 1
        divine += child_cnt
        child_cnt -= 1

        if divine >= m:
            child_cnt -= (divine - m)
            break

    print(root)
    for i in range(1, root):
        print(i, i + 1)

    last = n
    for i in range(child_cnt):
        print(root, last)
        last -= 1
    for i in range(n - root - child_cnt):
        print(root - 1, last)
        last -= 1


for _ in range(int(input())):
    solve()
