import sys

input = lambda: sys.stdin.readline().rstrip()

table = {}
for i, alphabet in enumerate("abcdefghijklmnopqrstuvwxyz"):
    table[alphabet] = i + 1

res = 0
input()
for i, char in enumerate(input()):
    res += table[char] * 31**i % 1234567891
    res %= 1234567891
    
print(res)
