import sys

input = lambda: sys.stdin.readline().rstrip()

MOD = 998244353

factorial = [1] * 202020
for i in range(2, len(factorial)):
    factorial[i] = factorial[i - 1] * i % MOD


def power(base: int, exp: int) -> int:
    ret = 1

    while exp:
        if exp & 1:
            ret = ret * base % MOD
        base = base * base % MOD
        exp >>= 1

    return ret


def combination(n: int, k: int):
    global factorial

    if n < 0:
        return 0
    if k < 0:
        return 0
    if n < k:
        return 0

    ret = factorial[n]
    ret = ret * power(factorial[k], MOD - 2) % MOD
    ret = ret * power(factorial[n - k], MOD - 2) % MOD

    return ret


def main():
    N = int(input())
    ranges = []
    renew_time = [[] for _ in range(N + 1)]

    for i in range(N):
        L, R = map(int, input().split())
        ranges.append((L, R))

        renew_time[L].append(i)
        renew_time[R + 1].append(i)
        renew_time[N - R].append(i)
        renew_time[N - L + 1].append(i)

    can_join_A = [0] * N
    can_join_B = [0] * N
    cnt = [[0] * 2 for _ in range(2)]
    cnt[0][0] = N

    answer = 0
    for sz in range(1, N):  # sz is size of A
        for i in renew_time[sz]:
            L, R = ranges[i]
            
            cnt[can_join_A[i]][can_join_B[i]] -= 1
            can_join_A[i] = 0
            can_join_B[i] = 0

            if L <= sz <= R:
                can_join_A[i] = 1
            if L <= N - sz <= R:
                can_join_B[i] = 1
            
            cnt[can_join_A[i]][can_join_B[i]] += 1
        
        if cnt[0][0] > 0:
            continue

        answer = (answer + combination(cnt[1][1], sz - cnt[1][0])) % MOD

    print(answer)
    


main()
