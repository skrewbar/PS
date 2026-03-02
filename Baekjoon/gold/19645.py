def main():
    N = int(input())
    a = list(map(int, input().split()))

    sum_a = sum(a)

    dp = [[False] * (sum_a + 1) for _ in range(sum_a + 1)]
    dp[0][0] = True
    for i in range(N):
        for j in range(sum_a, -1, -1):
            for k in range(sum_a - j, -1, -1):
                if j - a[i] >= 0 and dp[j - a[i]][k]:
                    dp[j][k] = True
                elif k - a[i] >= 0 and dp[j][k - a[i]]:
                    dp[j][k] = True

    answer = 0
    for j in range(sum_a, -1, -1):
        for k in range(j, -1, -1):
            if dp[j][k]:
                answer = max(answer, min(j, k, sum_a - j - k))

    print(answer)


main()
