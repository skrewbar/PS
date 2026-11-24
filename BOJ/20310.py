def main():
    S = input()

    cnt = [S.count("0") // 2, S.count("1") // 2]

    for i in range(len(S)):
        if S[i] == "0" and cnt[0]:
            cnt[0] -= 1
            print("0", end="")
        elif S[i] == "1":
            if cnt[1]:
                cnt[1] -= 1
                continue
            print("1", end="")


main()
