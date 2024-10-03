import sys

n = int(input())

three_corner = 4
two_corner = 4
edge = (n - 2) * 8
oneside = (n - 2) ** 2 * 5 + (n - 2) * 4

nums = list(map(int, input().split()))
if n == 1:
    print(sum(nums) - max(nums))
    sys.exit(0)

A, B, C, D, E, F = nums

one_min = min(nums)
two_min = min(
    A + B,
    A + C,
    A + D,
    A + E,
    B + C,
    B + D,
    B + F,
    C + E,
    C + F,
    D + E,
    D + F,
    E + F,
)
three_min = min(A, F) + min(D + E, B + D, B + C, C + E)

print(three_corner * three_min + (two_corner + edge) * two_min + one_min * oneside)
