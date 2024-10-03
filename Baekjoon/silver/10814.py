import sys

input = lambda: sys.stdin.readline().rstrip()

members = []
for _ in range(int(input())):
    member = input().split()
    member[0] = int(member[0])
    members.append(member)

members.sort(key=lambda x: x[0])

for i in range(len(members)):
    print(*members[i])
