import heapq


def main():
    INF = int(1e9)

    V, E, P = map(int, input().split())

    adj = [[] for _ in range(V + 1)]

    for _ in range(E):
        a, b, c = map(int, input().split())
        adj[a].append((b, c))
        adj[b].append((a, c))

    def getShortestDist(depart: int, dest: int) -> int:
        dist = [INF] * (V + 1)

        dist[depart] = 0

        heap = [(0, depart)]
        while heap:
            nowDist, now = heapq.heappop(heap)

            for nxt, edgeDist in adj[now]:
                nxtDist = nowDist + edgeDist

                if nxtDist < dist[nxt]:
                    dist[nxt] = nxtDist
                    heapq.heappush(heap, (nxtDist, nxt))

        return dist[dest]

    passThrough = getShortestDist(1, P) + getShortestDist(P, V)
    direct = getShortestDist(1, V)

    if passThrough == direct:
        print("SAVE HIM")
    else:
        print("GOOD BYE")


main()
