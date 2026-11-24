def main():
    N = int(input())

    A = list(map(int, input().split()))
    B = list(map(int, input().split()))

    time = sorted([-(-A[i] // B[i]) for i in range(N)], reverse=True)
    time.append(0)

    total_ability_count = 0
    answer = time[0]

    for i in range(N):
        diff = time[i] - time[i + 1]
        if diff == 0:
            continue

        required = diff * (i + 1)

        if total_ability_count + required <= answer - diff:
            total_ability_count += required
            answer -= diff
        else:
            diff = (answer - total_ability_count) // (i + 2)
            answer -= diff
            break

    print(answer)


main()
