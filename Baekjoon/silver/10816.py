N = int(input())
cards = {}
for i in map(int, input().split()):
    if not i in cards:
        cards[i] = 1
    else:
        cards[i] += 1


M = int(input())
for i in map(int, input().split()):
    if i in cards:
        print(cards[i], end=" ")
    else:
        print(0, end=" ")
