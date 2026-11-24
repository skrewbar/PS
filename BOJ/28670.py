def main():
    n, k = map(int, input().split())
    a = sorted(map(int, input().split()))

    lo = 0
    hi = n - 1

    answer = 0

    while lo < hi:
        if a[lo] + a[hi] > k:
            hi -= 1
            continue
        if a[lo] + a[hi] < k:
            lo += 1
            continue

        newLow = lo
        while newLow != hi and a[lo] == a[newLow]:
            newLow += 1

        newHigh = hi
        while newHigh != lo and a[hi] == a[newHigh]:
            newHigh -= 1

        answer += min(newLow - lo, hi - newHigh)

        lo = newLow
        hi = newHigh

    print(answer)


main()
