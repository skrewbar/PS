MOD = 10**9 + 7


def pow(base, exp):
    if exp == 0:
        return 1

    x = pow(base, exp // 2) % MOD

    return x * x % MOD if exp % 2 == 0 else x * x * base % MOD


input()  # t
input()  # n array

for k in map(int, input().split()):
    print(pow(2, k))
