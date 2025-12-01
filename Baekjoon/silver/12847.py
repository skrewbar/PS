def main():
    n, m = map(int, input().split())

    T = list(map(int, input().split()))

    sum_ = 0
    for i in range(m):
        sum_ += T[i]
    ans = sum_

    for i in range(m, n):
        sum_ += T[i] - T[i - m]
        ans = max(ans, sum_)

    print(ans)


main()
