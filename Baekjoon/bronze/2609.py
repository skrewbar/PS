import sys

input = lambda: sys.stdin.readline().rstrip()

a, b = map(int, input().split())


def gcd(a: int, b: int) -> int:
    while b != 0:
        a, b = b, a % b
    return a


G = gcd(a, b)
print(G)
print(a * b // G)
