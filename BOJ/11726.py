import sys

input = lambda: sys.stdin.readline().rstrip()

n = int(input())

ways = [0 for i in range(1001)]
ways[1] = 1
ways[2] = 2

for i in range(3, n + 1):
    ways[i] = (ways[i - 1] + ways[i - 2]) % 10007

print(ways[n])
