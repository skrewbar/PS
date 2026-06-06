import sys

input = lambda: sys.stdin.readline().rstrip()


def main():
    N, K, M = map(int, input().split())

    gem_by_c = [[(0, 0)] for _ in range(N + 1)]

    gems = []
    for i in range(N):
        C, V = map(int, input().split())

        gem = (V, i)

        gem_by_c[C].append(gem)
        gems.append(gem)

    used = [False] * (N)
    answer = 0
    for color in range(1, N + 1):
        gem_by_c[color].sort(reverse=True)
    gem_by_c.sort(key=lambda x: x[0][0], reverse=True)

    for color in range(M):
        gem = gem_by_c[color][0]
        answer += gem[0]
        used[gem[1]] = True
        K -= 1
        M -= 1

    gems.sort(reverse=True)
    i = 0
    for _ in range(K):
        while used[gems[i][1]]:
            i += 1

        answer += gems[i][0]
        i += 1

    print(answer)


main()
