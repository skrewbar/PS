import sys
from decimal import Decimal, ROUND_HALF_UP

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, K = map(int, input().split())

    scores = sorted(Decimal(input()) for _ in range(N))

    trimmed_mean = (sum(scores[K : N - K]) / Decimal(N - 2 * K)).quantize(
        Decimal("0.01"), rounding=ROUND_HALF_UP
    )
    print(trimmed_mean)

    for i in range(K):
        scores[i] = scores[K]
    for i in range(N - K, N):
        scores[i] = scores[N - K - 1]

    adjusted_mean = (sum(scores) / Decimal(N)).quantize(
        Decimal("0.01"), rounding=ROUND_HALF_UP
    )
    print(adjusted_mean)


main()
