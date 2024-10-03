N, M = map(int, input().split())

passwords = {}

for i in range(N):
    site, password = input().split()
    passwords[site] = password

for i in range(M):
    print(passwords[input()])
