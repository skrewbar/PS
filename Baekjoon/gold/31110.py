BOBO = "bobo"


def solve():
    n, m = map(int, input().split())
    c = "#" + input()

    adj = [[] for _ in range(n + 1)]
    for _ in range(m):
        a, b = map(int, input().split())
        adj[a].append(b)
        adj[b].append(a)

    counter_count = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in adj[i]:
            if c[i] != c[j]:
                counter_count[i] += 1

    answer = 0
    for i in range(1, n + 1):
        if c[i] != "o" or counter_count[i] < 2:
            continue

        for j in adj[i]:
            if c[j] != "b" or counter_count[j] < 2:
                continue

            answer += (counter_count[i] - 1) * (counter_count[j] - 1)

    print(answer)


def main():
    try:
        while True:
            solve()
    except EOFError:
        pass


main()
