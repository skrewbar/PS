def main():
    numbers = input()

    idx = 0
    i = 1
    while True:
        for c in str(i):
            if numbers[idx] == c:
                idx += 1

                if idx == len(numbers):
                    print(i)
                    return
        i += 1


main()
