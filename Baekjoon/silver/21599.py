def main():
    N = int(input())
    A = sorted(map(int, input().split()), reverse=True)

    r = -1

    for i in range(N):
        if A[i] == 0:
            break

        r = min(max(r, i + A[i] - 1), N - 1)

    print(r + 1)


main()
