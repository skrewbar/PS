Matrix = list[list[int]]

MOD = 10**9 + 7


def multiply_matrix(A: Matrix, B: Matrix) -> Matrix:
    res = [[0] * len(B[0]) for _ in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(A[0])):
                res[i][j] += A[i][k] * B[k][j] % MOD
                res[i][j] %= MOD
    return res


n = int(input())

res = [
    [1, 0],
    [0, 1],
]
base = [
    [1, 1],
    [1, 0],
]
while n:
    if n & 1:
        res = multiply_matrix(base, res)
    base = multiply_matrix(base, base)
    n >>= 1

print(res[0][0] * res[0][1] % MOD)
