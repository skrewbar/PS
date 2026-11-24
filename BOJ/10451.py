import sys

sys.setrecursionlimit(10**6)


def solve():
    N = int(input())
    arr = [0] + list(map(int, input().split()))

    visited = [False] * (N + 1)

    def dfs(cur: int) -> None:
        visited[cur] = True

        if not visited[arr[cur]]:
            dfs(arr[cur])

    answer = 0
    for i in range(1, N + 1):
        if not visited[i]:
            answer += 1
            dfs(i)

    print(answer)


def main():
    T = int(input())

    for _ in range(T):
        solve()


main()
