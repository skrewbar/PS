def solve():
    k, w = map(int, input().split())

    ans = 0
    prev_word = ""

    for _ in range(w):
        word = input()

        overlap = 0
        for i in range(k):
            if prev_word[-i - 1 :] != word[: i + 1]:
                continue

            overlap = max(overlap, i + 1)
        
        prev_word = word

        ans += k - overlap

    print(ans)


def main():
    n = int(input())
    for _ in range(n):
        solve()


main()
