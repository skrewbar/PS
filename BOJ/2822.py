def main():
    problems = sorted(((int(input()), i) for i in range(1, 8 + 1)), reverse=True)
    score = 0
    numbers = []

    for i in range(5):
        score += problems[i][0]
        numbers.append(problems[i][1])

    print(score)
    print(*sorted(numbers))


main()
