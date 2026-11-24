def solve(N: str):
    ans = 2

    for c in N:
        match c:
            case "0":
                ans += 4
            case "1":
                ans += 2
            case _:
                ans += 3

        ans += 1

    print(ans - 1)


def main():
    N = input()
    while N != "0":
        solve(N)
        N = input()


main()
