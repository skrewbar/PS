for i in sorted({input() for i in range(int(input()))}, key=lambda x: (len(x), x)):
    print(i)
