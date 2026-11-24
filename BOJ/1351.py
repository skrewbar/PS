n, p, q = map(int, input().split())

dp = {0: 1}


def infArr(i: int) -> int:
    if i in dp:
        return dp[i]

    dp[i] = infArr(i // p) + infArr(i // q)
    return dp[i]


print(infArr(n))

"""
functools의 cache를 이용한 풀이도 있습니다.
(1351-cache.py)
"""
