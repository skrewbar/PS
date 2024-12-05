input()
a = list(map(int, input().split()))
input()
b = list(map(int, input().split()))

if len(b) < len(a):
    a, b = b, a

a_begin = 0
b_begin = 0
answer = []
while True:
    max_common = -1
    for i in range(a_begin, len(a)):
        if a[i] not in b[b_begin:]:
            continue
        if max_common == -1 or a[max_common] < a[i]:
            max_common = i

    if max_common == -1:
        break

    for i in range(b_begin, len(b)):
        if b[i] == a[max_common]:
            b_begin = i + 1
            break

    answer.append(a[max_common])
    a_begin = max_common + 1

print(len(answer))
if len(answer):
    print(*answer)
