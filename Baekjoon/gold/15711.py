import sys
from typing import Callable

input = lambda: sys.stdin.readline().rstrip()


def createIsPrime() -> Callable[[int], bool]:
    LIMIT = int(2e6)
    sieve = [True] * (LIMIT + 1)

    sieve[0] = False
    sieve[1] = False

    primes = []

    for i in range(2, LIMIT + 1):
        if not sieve[i]:
            continue
        primes.append(i)
        for j in range(i + i, LIMIT + 1, i):
            sieve[j] = False

    def isPrime(n: int) -> bool:
        if n == 1:
            return False

        for p in primes:
            if p * p > n:
                break

            if n % p == 0:
                return False
        return True

    return isPrime


isPrime = createIsPrime()


def solve():
    A, B = map(int, input().split())

    if A + B < 4:
        print("NO")
        return
    if (A + B) % 2 == 1 and not isPrime(A + B - 2):
        print("NO")
        return
    print("YES")


def main():
    T = int(input())

    for _ in range(T):
        solve()


main()
