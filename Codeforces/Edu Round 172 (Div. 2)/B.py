from collections import Counter

for t in range(int(input())):
    n = int(input())
    colors = Counter(map(int, input().split()))

    alice_takable = True
    score = 0

    for marble, count in reversed(colors.most_common()):
        if count == 1:
            if alice_takable:
                score += 2
                alice_takable ^= 1
            else:
                alice_takable ^= 1
                continue
        else:
            score += 1
    print(score)
