def power(a, n, mod):
    if n == 0:
        return [1, 0, 0, 1]

    x = power(a, n // 2, mod)

    if not n % 2:
        arr = [(x[0] * x[0] + x[1] * x[2]) % mod,
               (x[0] * x[1] + x[1] * x[3]) % mod,
               (x[2] * x[0] + x[3] * x[2]) % mod,
               (x[2] * x[1] + x[3] * x[3]) % mod]
        return arr
    else:
        arr1 = [(x[0] * x[0] + x[1] * x[2]) % mod,
                (x[0] * x[1] + x[1] * x[3]) % mod,
                (x[2] * x[0] + x[3] * x[2]) % mod,
                (x[2] * x[1] + x[3] * x[3]) % mod]
        return [(arr1[0] + arr1[1]) % mod,
                arr1[0] % mod,
                (arr1[2] + arr1[3]) % mod,
                arr1[2] % mod]

def f(n, mod):
    a = [1, 1, 1, 0]
    return power(a, n, mod)[1]

def rec(fmod, cur):
    if fmod == int(1e21): return -1
    cycle = 15 * (fmod // 100)
    ret = -1
    for j in range(11):
        if f(cur, maxmod) == n % maxmod: ret = max(ret, cur)
        if f(cur, fmod) == n % fmod: ret = max(ret, rec(fmod * 10, cur))
        cur += cycle
    return ret

n = str(input().strip())
maxmod = pow(10, len(n))
n = int(n)
ans = -1
for i in range(1, 3000):
    if f(i, pow(10, 3)) == n % pow(10, 3): ans = max(ans, rec(10000, i))
if ans != -1 and len(str(ans)) < 101: print(ans)
else: print("NIE")