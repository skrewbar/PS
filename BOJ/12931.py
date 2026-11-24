from collections import deque


def main():
    # preprocess
    MAX_VALUE = 1000

    addCnt = [-1] * (MAX_VALUE + 1)
    mulCnt = [-1] * (MAX_VALUE + 1)

    addCnt[0] = 0
    mulCnt[0] = 0

    queue = deque([0])
    while queue:
        now = queue.popleft()

        if now * 2 <= MAX_VALUE and addCnt[now * 2] == -1:
            nxt = now * 2

            addCnt[nxt] = addCnt[now]
            mulCnt[nxt] = mulCnt[now] + 1
            queue.append(nxt)
        if now + 1 <= MAX_VALUE and addCnt[now + 1] == -1:
            nxt = now + 1

            addCnt[nxt] = addCnt[now] + 1
            mulCnt[nxt] = mulCnt[now]
            queue.append(nxt)

    # solve
    N = int(input())
    B = list(map(int, input().split()))

    print(max(map(lambda x: mulCnt[x], B)) + sum(map(lambda x: addCnt[x], B)))


main()
