from array import array
import sys


def read_int():
    ret = 0
    c = sys.stdin.read(1)
    while not c.isspace():
        ret *= 10
        ret += ord(c) - ord("0")
        c = sys.stdin.read(1)

    return ret


N = read_int()

total = N * (N - 1) // 2

for i in range(N):
    total -= read_int()

print(-total)
