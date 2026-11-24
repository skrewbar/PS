def main():
    BASES = "ACGT"

    S, P = map(int, input().split())
    dna = input()
    neededCnt = {k: v for k, v in zip(BASES, map(int, input().split()))}
    cnt = {i: 0 for i in BASES}

    def isSecure() -> bool:
        for base in BASES:
            if cnt[base] < neededCnt[base]:
                return False
        return True

    for i in range(P):
        cnt[dna[i]] += 1

    ans = 1 if isSecure() else 0
    for i in range(P, S):
        cnt[dna[i]] += 1
        cnt[dna[i - P]] -= 1

        if isSecure():
            ans += 1

    print(ans)


main()
