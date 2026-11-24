from collections import namedtuple

Food = namedtuple("Food", ["expiration", "saturation"])


def solve(caseNum: int):
    N = int(input())
    foods = [Food(*map(int, input().split())) for _ in range(N)]

    ans = 0

    def findAns(eaten: list[bool], limit: int):
        nonlocal ans
        ans = max(ans, limit)

        for i in range(N):
            if eaten[i]:
                continue
            if foods[i].expiration < limit:
                continue

            eaten[i] = True
            findAns(eaten, limit + foods[i].saturation)
            eaten[i] = False

    findAns([False] * N, 0)

    print(f"Case #{caseNum}: {ans}")


def main():
    T = int(input())
    for i in range(1, T + 1):
        solve(i)


main()
