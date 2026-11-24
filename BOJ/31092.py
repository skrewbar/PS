from typing import NamedTuple
from collections import defaultdict


class Sticker(NamedTuple):
    alphabet: str
    detach_cost: int
    purchase_cost: int


INF = int(1e9)


def main():
    N, M, K = map(int, input().split())

    stickers: list[Sticker] = []
    cheapest_cost: defaultdict[str, int] = defaultdict(lambda: INF)
    for i in range(M):
        s, d, a = input().split()
        d, a = map(int, (d, a))

        stickers.append(Sticker(s, d, a))

        if a < cheapest_cost[s]:
            cheapest_cost[s] = a

    b = list(map(lambda x: int(x) - 1, input().split()))

    S = input()

    ans = INF
    for i in range(N - K + 1):
        can_be_substr = True
        for j in range(K):
            sticker = stickers[b[i + j]]
            if sticker.alphabet == S[j]:
                continue

            if S[j] not in cheapest_cost:
                can_be_substr = False
                break

        if not can_be_substr:
            continue

        detach_costs: defaultdict[str, list[int]] = defaultdict(list)
        for j in range(i):
            sticker = stickers[b[j]]
            detach_costs[sticker.alphabet].append(sticker.detach_cost)
        for j in range(i + K, N):
            sticker = stickers[b[j]]
            detach_costs[sticker.alphabet].append(sticker.detach_cost)

        cost = 0
        for j in range(K):
            sticker = stickers[b[i + j]]
            if sticker.alphabet == S[j]:
                continue

            cost += sticker.detach_cost
            detach_costs[sticker.alphabet].append(0)

        for key in detach_costs:
            detach_costs[key].sort(reverse=True)

        for j in range(K):
            sticker = stickers[b[i + j]]
            if sticker.alphabet == S[j]:
                continue

            if detach_costs[S[j]] and detach_costs[S[j]][-1] < cheapest_cost[S[j]]:
                cost += detach_costs[S[j]].pop()
            else:
                cost += cheapest_cost[S[j]]

        ans = min(ans, cost)

    print(-1 if ans == INF else ans)


main()
