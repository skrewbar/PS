fib = [[1, 0], [0, 1]]  # (An, 0개수, 1개수)


def f(n):
    if n == 0:
        return fib[0]
    elif n == 1:
        return fib[1]
    elif len(fib) > n:
        return fib[n]
    else:
        Fn1 = f(n - 1)
        Fn2 = f(n - 2)
        Fn = [Fn1[0] + Fn2[0], Fn1[1] + Fn2[1]]
        fib.append(Fn)
        return Fn


for i in range(int(input())):
    Fn = f(int(input()))
    print(Fn[0], Fn[1])