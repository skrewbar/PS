import sys

input = lambda: sys.stdin.readline().rstrip()


def bellman_ford(vertexCount: int, graph: list[tuple[int, int, int]]) -> bool:
    time = [0 for _ in range(vertextCount + 1)]
    for i in range(vertexCount):
        for current, next, nextTime in graph:
            if time[current] + nextTime < time[next]:
                time[next] = time[current] + nextTime

                if i == vertexCount - 1:
                    return True
    return False


for testCase in range(int(input())):
    vertextCount, pathCount, wormholeCount = map(int, input().split())
    graph = []

    for _ in range(pathCount):
        v1, v2, time = map(int, input().split())
        graph.append((v1, v2, time))
        graph.append((v2, v1, time))

    for _ in range(wormholeCount):
        from_, to, time = map(int, input().split())
        graph.append((from_, to, -time))

    print(["NO", "YES"][bellman_ford(vertextCount, graph)])
