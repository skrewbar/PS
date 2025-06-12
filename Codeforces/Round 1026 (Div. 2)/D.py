def solve():
    n, m = map(int, input().split())

    battery = list(map(int, input().split()))

    adj = [[] for _ in range(n)]
    for _ in range(m):
        s, t, w = map(int, input().split())
        s -= 1
        t -= 1

        adj[s].append((t, w))
        adj[t].append((s, w))

    lo = 0
    hi = 10**9 * n
    reachable = False
    while lo < hi:
        mid = (lo + hi) // 2

        dp = [-1] * n
        dp[0] = min(battery[0], mid)
        for i in range(n):
            for next_, need in adj[i]:
                if dp[i] >= need:
                    dp[next_] = max(dp[next_], dp[i] + battery[next_])
                    dp[next_] = min(dp[next_], mid)

        if dp[n - 1] == -1:
            lo = mid + 1
        else:
            reachable = True
            hi = mid

    print(lo if reachable else -1)


for _ in range(int(input())):
    solve()
