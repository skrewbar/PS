for t in range(int(input())):
    n, k = map(int, input().split())
    cans = sorted(map(int, input().split()))
    count = 0
    lower = 0

    for i in range(n):
        cans[i] -= lower

        if k <= (n - i) * cans[i]:
            count += k
            break

        k -= (n - i) * cans[i]
        count += (n - i) * cans[i] + 1
        lower += cans[i]

    print(count)
