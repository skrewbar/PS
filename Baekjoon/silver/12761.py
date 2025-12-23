from collections import deque

MAX_NUM = 100_000


def main():
    A, B, N, M = map(int, input().split())

    queue = deque()
    ans = [-1] * (MAX_NUM + 1)

    queue.append(N)
    ans[N] = 0

    while queue:
        now = queue.popleft()

        for nxt in (
            now + 1,
            now - 1,
            now + A,
            now - A,
            now + B,
            now - B,
            now * A,
            now * B,
        ):
            if nxt < 0 or nxt > MAX_NUM:
                continue
            if ans[nxt] != -1:
                continue
            if nxt == M:
                print(ans[now] + 1)
                return

            ans[nxt] = ans[now] + 1
            queue.append(nxt)


main()
