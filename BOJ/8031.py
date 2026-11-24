import sys

input = lambda: sys.stdin.readline().rstrip()

sys.setrecursionlimit(10**6)


isPrime = [True] * 101
isPrime[1] = False
for i in range(2, len(isPrime)):
    if not isPrime[i]:
        continue

    for j in range(i + i, len(isPrime), i):
        isPrime[j] = False

oddPrimes = []
for i in range(3, len(isPrime)):
    if isPrime[i]:
        oddPrimes.append(i)

bigPrimes = [
    1000000007,
    500000041,
    250000073,
    125000077,
    62500073,
    31250047,
    15625061,
    7812551,
    3906293,
    1953157,
    976601,
    488311,
    244177,
    122099,
    61091,
    30557,
    15289,
    7669,
    3847,
    1949,
    991,
    509,
    269
]


def solve():
    k = int(input())

    ans = []

    for p in bigPrimes:
        if k >= p + 10:
            k -= p
            ans.append(p)

    def decompose(k: int, hi: int) -> bool:
        if k == 0:
            return True

        for i in range(hi - 1, -1, -1):
            if oddPrimes[i] > k:
                continue

            ans.append(oddPrimes[i])
            if decompose(k - oddPrimes[i], i):
                return True
            ans.pop()

        return False

    decompose(k, len(oddPrimes))
    print(len(ans))
    print(*sorted(ans))


def main():
    for _ in range(int(input())):
        solve()


main()
