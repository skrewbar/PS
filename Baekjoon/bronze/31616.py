def main():
    N = int(input())
    S = input()

    print("Yes" if S.count(S[0]) == N else "No")


main()
