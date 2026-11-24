T = int(input())

for case in range(T):
    score = 0
    recent = 0
    quiz = input()
    for char in quiz:
        if char == "O":
            score += 1 + recent
            recent += 1
        else:
            recent = 0
    print(score)
