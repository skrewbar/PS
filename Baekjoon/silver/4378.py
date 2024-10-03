import sys

input = lambda: sys.stdin.readline().rstrip()

keyboards = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./"

cor_table = {" ": " "}
for i in range(1, len(keyboards)):
    cor_table[keyboards[i]] = keyboards[i - 1]

while True:
    i = input()
    if i == "":
        break
    for char in i:
        print(cor_table[char], end="")
    print()
