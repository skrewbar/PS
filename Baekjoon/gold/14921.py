def main():
    N = int(input())
    A = list(map(int, input().split()))

    l = 0
    r = N - 1

    ans = A[0] + A[1]

    while l < r:
        if abs(A[l] + A[r]) < abs(ans):
            ans = A[l] + A[r]

        if A[l] + A[r] < 0:
            l += 1
        else:
            r -= 1

    print(ans)


main()
