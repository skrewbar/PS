import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, M, Q = map(int, input().split())

    value = [0] * (N + 1)
    for i, d in enumerate(map(int, input().split()), 1):
        value[i] -= d
    for i, e in enumerate(map(int, input().split()), 1):
        value[i] += e
    added_value = [0] * (N + 1)

    rt = int(M ** (1 / 2))

    adj = [[] for _ in range(N + 1)]
    degree = [0] * (N + 1)

    for _ in range(M):
        u, v = map(int, input().split())

        adj[u].append(v)
        adj[v].append(u)

        degree[u] += 1
        degree[v] += 1

    for i in range(1, N + 1):
        adj[i].sort(key=lambda v: -degree[v])

    for i in range(1, N + 1):
        if degree[i] > rt:
            continue
        for neighbor in adj[i]:
            added_value[neighbor] += value[i]

    for _ in range(Q):
        tp, *args = input().split()

        if tp == "add":
            count = int(args[0])
            if args[1] == "desk":
                count = -count
            label = int(args[2])

            value[label] += count
            if degree[label] > rt:
                continue

            for neighbor in adj[label]:
                added_value[neighbor] += count
        else:
            label = int(args[0])

            v = value[label] + added_value[label]
            for neighbor in adj[label]:
                if degree[neighbor] <= rt:
                    break
                v += value[neighbor]

            if v < 0:
                print("desks")
            elif v > 0:
                print("monitors")
            else:
                print("same")


main()
