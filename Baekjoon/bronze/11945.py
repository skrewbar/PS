def main() -> None:
    n, m = map(int, input().split())
    fishBread: list[list[int]] = []
    for _ in range(n):
        fishBread.append("".join(reversed(list(input()))))

    for i in range(n):
        for j in range(m):
            print(fishBread[i][j], end="")
        print()


if __name__ == "__main__":
    main()