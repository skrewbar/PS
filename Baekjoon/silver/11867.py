import sys

input = lambda: sys.stdin.readline().rstrip()

n, m = map(int, input().split())

print("A") if n % 2 + m % 2 < 2 else print("B")
