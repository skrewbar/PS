def main() -> None:
    n: int = int(input())
    for i in range(1, 2 * n):
        if i <= n:
            print(" " * (n - i) + "*" * i + "*" * (i - 1))
        else:
            print(" " * (i - n) + "*" * (2 * n - i) + "*" * (2 * n - 1 - i))


if __name__ == "__main__":
    main()
