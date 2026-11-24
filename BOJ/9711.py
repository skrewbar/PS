def main():
    fib = [0] * 10_001
    fib[1] = 1

    for i in range(2, len(fib)):
        fib[i] = fib[i - 1] + fib[i - 2]
    
    for case in range(1, int(input()) + 1):
        P, Q = map(int, input().split())

        print(f"Case #{case}: {fib[P] % Q}")

main()
