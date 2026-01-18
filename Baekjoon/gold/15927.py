def main():
    S = input()

    if S.count(S[0]) == len(S):
        print(-1)
    elif S != S[::-1]:
        print(len(S))
    else:
        print(len(S) - 1)


main()
