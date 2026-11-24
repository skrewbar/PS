word = input()
answer = ""

for char in word:
    if char.isupper():
        answer += char.lower()
    else:
        answer += char.upper()

print(answer)