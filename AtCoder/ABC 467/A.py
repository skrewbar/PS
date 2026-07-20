import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    H, W = map(int, input().split())

    if W * 10000 >= 25 * H * H:
        print("Yes")
    else:
        print("No")


main()

