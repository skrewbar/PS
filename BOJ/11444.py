hash_map = {0: 0, 1: 1, 2: 1}
mod = 10_0000_0007


def f(n: int) -> int:
    if n in hash_map:
        return hash_map[n]
    else:
        if n % 2 == 0:
            hash_map[n] = (f(n // 2) * (f(n // 2 + 1) + f(n // 2 - 1))) % mod
            return hash_map[n]
        else:
            hash_map[n] = (
                (f((n + 1) // 2) ** 2) % mod + (f((n - 1) // 2) ** 2) % mod
            ) % mod
            return hash_map[n]


print(f(int(input())))
