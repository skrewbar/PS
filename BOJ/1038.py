def main():
    N = int(input())

    def backtrack(ans: list[int], length: int):
        nonlocal N

        if len(ans) == length:
            N -= 1

            if N == -1:
                print(*ans, sep="")

            return

        for i in range(10):
            if ans and i >= ans[-1]:
                continue

            ans.append(i)
            backtrack(ans, length)
            ans.pop()

    length = 1
    while N >= 0:
        if length > 10:
            print(-1)
            return

        backtrack([], length)
        length += 1


main()
