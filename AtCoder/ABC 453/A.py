import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N = int(input())
    S = input()

    i = 0
    while i < N and S[i] == "o":
        i += 1
    
    print(S[i:])


main()
