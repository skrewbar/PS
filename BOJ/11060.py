def main():
    INF = int(1e9)

    N = int(input())
    A = list(map(int, input().split()))

    ans = [INF] * N
    ans[0] = 0
    for i in range(N):
        for j in range(i, min(i + A[i] + 1, N)):
            ans[j] = min(ans[j], ans[i] + 1)

    print(ans[-1] if ans[-1] != INF else -1)


main()
