L, R = input().split()
L = list(L)
R = list(R)

count = 0
if len(L) == len(R):
    for i in range(len(L)):
        if R[i] == L[i] == "8":
            count += 1
        elif R[i] == L[i]:
            continue
        else:
            break


print(count)
