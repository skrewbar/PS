def get_one_count(n: int) -> int:
    if n == 0:
        return 0

    digit = 0
    while 1 << digit <= n:
        digit += 1
    digit -= 1

    ret = 0
    for i in range(digit):
        ret += n // (2 ** (i + 1)) * (2**i)
        if (n >> i) & 1:
            ret += n % (2**i) + 1

    ret += n % (2**digit) + 1
    return ret


a, b = map(int, input().split())
print(get_one_count(b) - get_one_count(a - 1))
