import sys

input = lambda: sys.stdin.readline().rstrip()


def manacher(string: str) -> list[int]:
    a = [0] * len(string)
    c = 0
    r = 0

    for i in range(len(string)):
        if i <= r:
            a[i] = min(a[2 * c - i], r - i)
        else:
            a[i] = 0

        while (
            i - a[i] - 1 >= 0
            and i + a[i] + 1 < len(string)
            and string[i - a[i] - 1] == string[i + a[i] + 1]
        ):
            a[i] += 1

        if r < i + a[i]:
            r = i + a[i]
            c = i
    return a


N = int(input())
numbers = input().rstrip().split()
numbers = "0" + "0".join(numbers) + "0"
a = manacher(numbers)

for i in range(int(input())):
    S, E = map(lambda x: int(x) - 1, input().split())
    if a[S + E + 1] >= (E - S + 1):
        print(1)
    else:
        print(0)
