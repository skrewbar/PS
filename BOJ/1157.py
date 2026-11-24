alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
table = {i:0 for i in alphabets}
for i in input().upper():
    table[i] += 1
count_sorted = sorted(table, key=lambda x:table[x], reverse=True)
max1, max2 = count_sorted[0], count_sorted[1]
if table[max1] == table[max2]:
    print("?")
else:
    print(max1)