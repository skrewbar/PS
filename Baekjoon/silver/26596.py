from collections import defaultdict

m = int(input())
amount = defaultdict(int)

for _ in range(m):
    name, quantity = input().split()
    amount[name] += int(quantity)

gold = False
for i in amount:
    if gold:
        break
    for j in amount:
        if i == j:
            continue

        if amount[i] * 1618 // 1000 == amount[j]:
            gold = True
            break

print("Delicious!" if gold else "Not Delicious...")
