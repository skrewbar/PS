def main():
    N = int(input())
    M = int(input())
    K = int(input())

    pos = [int(input()) for _ in range(M)]

    lo = 0
    answer = 0

    for p in pos:
        while lo + 1 < p - K:
            answer += 1
            lo += 2 * K + 1

        lo = max(lo, p + K)

    while lo < N:
        answer += 1
        lo += 2 * K + 1

    print(answer)


main()
