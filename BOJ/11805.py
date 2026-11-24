from math import log2, floor


def solve(case: int):
    H, L = map(int, input().split())

    answer = 2 * L - 1

    if (1 << floor(log2(L))) != L:
        answer += 2 * (1 << floor(log2(L))) - L
        H -= 1
    H -= floor(log2(L))

    answer += H * L

    print(f"Case {case}: {answer}")


def main():
    T = int(input())
    for i in range(1, T + 1):
        solve(i)


main()
