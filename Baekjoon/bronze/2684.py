def main():
    coinSeqs = []
    for coins in range(1 << 3):
        s = []

        for i in range(3):
            s.append("H" if coins & (1 << i) else "T")
        coinSeqs.append("".join(reversed(s)))

    def solve():
        resSeq = input()
        for seq in coinSeqs:
            ans = 0

            for i in range(38):
                if resSeq[i : i + 3] == seq:
                    ans += 1
            print(ans, end=" ")

        print()

    P = int(input())
    for _ in range(P):
        solve()


main()
