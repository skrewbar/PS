import sys

sys.setrecursionlimit(10**6)


def gcd(a: int, b: int) -> int:
    while b:
        a, b = b, a % b
    return a


def lcm(a: int, b: int) -> int:
    return a * b // gcd(a, b)


def main() -> None:
    N = int(input())
    shuffleArr = list(map(lambda x: int(x) - 1, input().split()))

    visited = [False] * N

    def getCycleLen(now: int) -> int:
        visited[now] = True

        nxt = shuffleArr[now]

        if visited[nxt]:
            return 1

        return getCycleLen(nxt) + 1

    ans = 1
    for i in range(N):
        if not visited[i]:
            ans = lcm(ans, getCycleLen(i))

    print(ans)


main()
