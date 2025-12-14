def main():
    N = int(input())

    ans = 0
    res = 1

    for _ in range(N):
        res *= float(input())
        ans = max(ans, res)

        if res < 1:
            res = 1

    print(f"{ans:.3f}")


main()
