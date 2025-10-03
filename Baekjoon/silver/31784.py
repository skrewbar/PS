N, K = map(int, input().split())
S = list(input())

aord = lambda c: ord(c) - ord("A")
achr = lambda x: chr(x + ord("A"))

for i in range(N):
    if S[i] == "A":
        continue

    if K >= aord("Z") - aord(S[i]) + 1:
        K -= aord("Z") - aord(S[i]) + 1
        S[i] = "A"

S[-1] = achr((aord(S[-1]) + K) % 26)
print("".join(S))
