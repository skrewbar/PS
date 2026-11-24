def main():
    N = int(input())
    A = list(map(int, input().split()))

    cnt: dict[int, int] = {}
    for i in range(N):
        if not A[i] in cnt:
            cnt[A[i]] = 0
        cnt[A[i]] += 1

    if max(cnt.values()) > N // 2:
        print(-1)
        return

    indices = sorted(range(N), key=lambda i: A[i])
    for i in range((N + 1) // 2):
        j = i + N // 2
        A[indices[i]], A[indices[j]] = A[indices[j]], A[indices[i]]

    print(*A)


main()
