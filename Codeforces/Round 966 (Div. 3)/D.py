for t in range(int(input())):
    n = int(input())
    numbers = list(map(int, input().split()))
    prefixSum = list(numbers)

    for i in range(n - 1):
        prefixSum[i + 1] += prefixSum[i]

    strip = input()
    score = 0
    l = 0
    r = n - 1

    while l < r:
        if strip[l] != "L":
            l += 1
            continue
        if strip[r] != "R":
            r -= 1
            continue

        score += prefixSum[r] - prefixSum[l] + numbers[l]
        l += 1
        r -= 1

    print(score)
