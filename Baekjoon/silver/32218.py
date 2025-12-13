def main():
    n = int(input())
    a = list(map(int, input().split()))

    cnt = 0

    while True:
        cnt += 1

        b = [0] * n

        for i in range(n):
            for j in range(i + 1, n):
                if a[j] > a[i]:
                    b[i] += 1

        if a == b:
            break
        a = b

    print(cnt)


main()
