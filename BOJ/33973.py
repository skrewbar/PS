import sys

input = lambda: sys.stdin.readline().rstrip()

MOD = 998244353


def factorial(n: int, mod: int = MOD):
    ret = 1

    for i in range(2, n + 1):
        ret = (ret * i) % mod

    return ret


def main():
    N, Q = map(int, input().split())

    arrays = [tuple(map(int, input().split())) for _ in range(N)]

    check_list = []
    for _ in range(Q):
        tp, i = map(int, input().split())
        i -= 1
        arrays.sort(key=lambda arr: arr[i])

        if not check_list and tp == 2:
            continue

        if tp == 1:
            check_list = [i]
        else:
            check_list.append(i)

    if not check_list:
        print(1)
        return

    check_tuples = [tuple(arrays[i][check] for check in check_list) for i in range(N)]
    count = {}

    for tup in check_tuples:
        if tup not in count:
            count[tup] = 1
        else:
            count[tup] += 1

    answer = 1
    for tup in check_tuples:
        answer *= factorial(count[tup])
        answer %= MOD

        count[tup] = 0

    print(answer)


main()
