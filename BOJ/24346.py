string = sorted(input())
answer = 0
counted = False

while len(string) > 0:
    last = string.pop()
    if len(string) > 0 and last == string[-1]:
        string.pop()
    else:
        answer += 1
        counted = True

if not counted:
    answer += 1
print(answer)
