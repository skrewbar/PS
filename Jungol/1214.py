import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    n, *h = list(map(int, input().split()))
    h = [0, *h, 0]

    ans = 0

    stk = [0]
    for i in range(1, n + 2):
        top = stk[-1]

        while h[top] > h[i]:
            height = h[top]
            stk.pop()
            top = stk[-1]
            ans = max(ans, (i - top - 1) * height)

        stk.append(i)

    print(ans)


main()
