from heapq import *

studentCount, lineCount, partyLocation = map(int, input().split())

toPartyLines = [[] for _ in range(studentCount + 1)]
fromPartyLines = [[] for _ in range(studentCount + 1)]
for i in range(lineCount):
    from_, to, time = map(int, input().split())
    toPartyLines[from_].append((to, time))
    fromPartyLines[to].append((from_, time))


def dijkstra(graph: list[list[tuple[int, int]]], start: int) -> list[int]:
    heapq = [(0, start)]
    time = [float("inf")] * (studentCount + 1)
    time[start] = 0

    while heapq:
        currentTime, currentLoc = heappop(heapq)
        if time[currentLoc] < currentTime:
            continue
        for nextLoc, nextTime in graph[currentLoc]:
            cost = nextTime + currentTime
            if cost < time[nextLoc]:
                time[nextLoc] = cost
                heappush(heapq, (cost, nextLoc))

    return time[1:]


maxTime = 0
for i, j in zip(
    dijkstra(toPartyLines, partyLocation), dijkstra(fromPartyLines, partyLocation)
):
    maxTime = max(i + j, maxTime)

print(maxTime)

print(dijkstra(toPartyLines, partyLocation))
print(dijkstra(fromPartyLines, partyLocation))