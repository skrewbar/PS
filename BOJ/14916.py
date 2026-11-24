def main():
    n = int(input())

    five = n // 5

    while five >= 0:
        if (n - five * 5) % 2 == 0:
            break
        five -= 1

    if five < 0:
        print(-1)
    else:
        print(five + (n - 5 * five) // 2)


main()
