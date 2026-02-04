def main():
    N = int(input())

    for i in range(1, N + 1):
        print(f"Case #{i}:", *input().split()[::-1])


main()
