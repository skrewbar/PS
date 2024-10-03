import sys

input = lambda: sys.stdin.readline().rstrip()


n = input()
set_ = {a for a in input().split()}
m = input()

for b in input().split():
    if b in set_:
        print(1)
    else:
        print(0)
