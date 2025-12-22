from collections import defaultdict


def solve():
    M = input()

    count = defaultdict(int)
    i = 0
    while i < len(M):
        count[M[i]] += 1

        if count[M[i]] == 3:
            if i + 1 >= len(M) or M[i + 1] != M[i]:
                print("FAKE")
                return
            count[M[i]] = 0
            i += 2
        else:
            i += 1

    print("OK")


def main():
    for _ in range(int(input())):
        solve()


main()
