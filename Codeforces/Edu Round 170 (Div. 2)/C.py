for t in range(int(input())):
    n, k = map(int, input().split())
    arr = sorted(map(int, input().split()))

    answer = 1
    count = 1
    kind = 1

    l, r = 0, 1

    while r < n:
        if arr[r] == arr[r - 1]:
            count += 1

        elif arr[r] == arr[r - 1] + 1:
            if kind == k:
                answer = max(answer, count)
                while kind == k:
                    l += 1
                    count -= 1
                    if arr[l] != arr[l - 1]:
                        kind -= 1
            kind += 1
            count += 1

        else:
            answer = max(answer, count)
            count = 1
            kind = 1
            l = r
        r += 1

    print(max(answer, count))
