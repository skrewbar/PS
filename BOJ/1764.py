import sys

input = lambda: sys.stdin.readline().rstrip()

N, M = map(int, input().split())

never_listened = {input() for i in range(N)}

neither = sorted(filter(lambda x: x in never_listened, [input() for i in range(M)]))
print(len(neither))
for name in neither:
    print(name)
