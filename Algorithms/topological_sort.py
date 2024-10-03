from collections import deque


def kahn(nodes: list[int], indegree: list[int], graph: list[list[int]]) -> list[int]:
    queue = deque()
    sortedList = []
    for node in nodes:
        if indegree[node] == 0:
            queue.append(node)

    while queue:
        node = queue.popleft()
        sortedList.append(node)

        for next in graph[node]:
            indegree[next] -= 1
            if indegree[next] == 0:
                queue.append(next)

    return sortedList
