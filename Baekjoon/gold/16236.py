N = int(input())
space = []
for i in range(N):
    space.append(list(map(int, input().split())))


shark = None
for x in range(N):
    for y in range(N):
        if space[x][y] == 9:
            shark = (x, y)
time = 0
size = 2
eat_count = 0
Xs, Ys = shark[0], shark[1]


def getFish(start: tuple):
    graph = {}
    for x in range(N):
        for y in range(N):
            nxt_list = []
            if (0 <= x - 1) and (0 <= space[x - 1][y] <= size):
                nxt_list.append((x - 1, y))
            if (x + 1 <= N - 1) and (0 <= space[x + 1][y] <= size):
                nxt_list.append((x + 1, y))
            if (0 <= y - 1) and (0 <= space[x][y - 1] <= size):
                nxt_list.append((x, y - 1))
            if (y + 1 <= N - 1) and (0 <= space[x][y + 1] <= size):
                nxt_list.append((x, y + 1))
            graph[(x, y)] = nxt_list

    fish_list = []
    visited = {i: False for i in graph.keys()}
    distance = {i: 0 for i in graph.keys()}
    queue = [start]
    visited[start] = True
    while len(queue) > 0:
        current = queue.pop(0)
        for nxt in graph[current]:
            if not visited[nxt]:
                x, y = nxt[0], nxt[1]
                d = distance[current] + 1
                distance[nxt] = d
                if 0 < space[x][y] < size:
                    fish_list.append((x, y, d))
                queue.append(nxt)
                visited[nxt] = True
    return fish_list


while True:
    fish_list = getFish((shark[0], shark[1]))

    if len(fish_list) == 0:
        break
    fish = (None, None, N**2)
    for f in fish_list:
        if f[2] < fish[2]:
            fish = f
        elif f[2] == fish[2]:
            if f[0] < fish[0]:
                fish = f
            elif f[0] == fish[0]:
                if f[1] < fish[1]:
                    fish = f

    time += fish[2]  # 이동거리 만큼 시간 증가
    eat_count += 1  # 물고기 먹었으니 +=1
    Xs, Ys = shark[0], shark[1]
    Xf, Yf = fish[0], fish[1]
    space[Xs][Ys] = 0
    space[Xf][Yf] = 9
    shark = (Xf, Yf)
    if eat_count == size:  # 많이 먹었으면 크기 늘리기
        size += 1
        eat_count = 0


print(time)
