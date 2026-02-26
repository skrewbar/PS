from math import factorial


def get_cases(length: int, count: list[int]) -> int:
    ret = factorial(length)
    for c in count:
        ret //= factorial(c)
    return ret


def main():
    N, M = map(int, input().split())
    S = list(map(int, input()))

    answer = 0
    count = [0] * M
    for i in S:
        count[i] += 1
    determined_count = 0
    for i in range(M - 1, 0, -1):
        if count[i] == 0:
            continue

        # compute cases which have less digit i than S
        for j in range(count[i]):

            undetermined = N - determined_count

            cases = factorial(N) // factorial(undetermined)
            for k in range(M - 1, i, -1):
                cases //= factorial(count[k])
            cases //= factorial(j)

            cases *= i**undetermined
            answer += cases

            determined_count += 1

    for i in range(N - 1, -1, -1):
        cases = 0

        for j in range(S[i]):
            if count[j] == 0:
                continue
            count[j] -= 1
            cases += get_cases(i, count)
            count[j] += 1

        count[S[i]] -= 1

        answer += cases

    print(answer)


main()
