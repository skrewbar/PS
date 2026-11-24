n = int(input())

string = input()

max_length = 0
alphabets = {}
kind = 0
left = 0
right = 0

while right < len(string):
    if string[right] not in alphabets:
        alphabets[string[right]] = 0
    alphabets[string[right]] += 1

    if alphabets[string[right]] == 1:
        kind += 1

    while kind > n:
        alphabets[string[left]] -= 1
        if alphabets[string[left]] == 0:
            kind -= 1
        left += 1

    max_length = max(right - left + 1, max_length)
    right += 1

print(max_length)
