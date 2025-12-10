from collections import deque


def main():
    N, M = map(int, input().split())

    origins = {chr(i) for i in range(ord("A"), ord("A") + N)}
    adj = {chr(i): [] for i in range(ord("A"), ord("A") + N)}

    for _ in range(M):
        A, B = input().split()
        adj[A].append(B)

        if B in origins:
            origins.remove(B)

    arrested = set(list(input().split())[1:])
    visited = set()
    queue = deque()

    for i in origins:
        if not i in arrested:
            visited.add(i)
            queue.append(i)

    ans = 0
    while queue:
        now = queue.popleft()

        for nxt in adj[now]:
            if nxt in visited or nxt in arrested:
                continue
            visited.add(nxt)
            ans += 1
            queue.append(nxt)

    print(ans)


main()
