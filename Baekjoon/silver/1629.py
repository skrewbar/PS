A, B, C = map(int, input().split())


# A^B%C = ?
def power(B: int) -> int:
    if B == 1:
        return A % C

    k = power(B // 2)

    if B % 2 == 0:
        return k**2 % C
    else:
        return k**2 % C * A % C


print(power(B))
