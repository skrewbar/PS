import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N = int(input())

    pairs = []

    for _ in range(N):
        pairs.append(tuple(map(int, input().split())))

    pairs.sort(key=lambda x: x[1])
    print(sum(map(sum, pairs)) - pairs[-1][1])


main()
