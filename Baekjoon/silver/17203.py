def main():
    N, Q = map(int, input().split())
    a = [0] + list(map(int, input().split()))

    for _ in range(Q):
        i, j = map(int, input().split())
        answer = 0

        for k in range(i, j):
            answer += abs(a[k + 1] - a[k])

        print(answer)


main()
