import sys

input = lambda: sys.stdin.readline().rstrip()


s = input()
exp = list(input())
len_ = len(exp)
a = []

for char in s:
    a.append(char)
    if a[-1] == exp[-1] and a[-len_:] == exp:
        del a[-len_:]

a = "".join(a)
if not a:
    print("FRULA")
else:
    print(a)
