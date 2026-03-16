import sys

input = lambda: sys.stdin.readline().rstrip()


dx = [1, -1, 0, 0, 0, 0]
dy = [0, 0, 1, -1, 0, 0]
dz = [0, 0, 0, 0, 1, -1]


def is_invalid_coord(x: int, y: int, z: int):
    return x < 0 or y < 0 or z < 0 or x > 4 or y > 4 or z > 4


def solve():
    P = int(input())
    is_center = [[[False] * 5 for _ in range(5)] for _ in range(5)]
    coords = []

    while len(coords) < P:
        for coord_str in input().split():
            coord = tuple(map(int, coord_str.split(",")))
            coords.append(coord)

            x, y, z = coord
            if is_center[x][y][z]:
                print("NO", len(coords))
                return
            is_center[x][y][z] = True

    surface_cnt = P * 6
    visited = [[[False] * 5 for _ in range(5)] for _ in range(5)]

    def visit_component(x: int, y: int, z: int):
        nonlocal surface_cnt

        visited[x][y][z] = True

        for k in range(len(dx)):
            nx = x + dx[k]
            ny = y + dy[k]
            nz = z + dz[k]

            if is_invalid_coord(nx, ny, nz) or not is_center[nx][ny][nz]:
                continue

            surface_cnt -= 1

            if visited[nx][ny][nz]:
                continue

            visit_component(nx, ny, nz)

    visit_component(*coords[0])
    for i in range(P):
        x, y, z = coords[i]
        if not visited[x][y][z]:
            print("NO", i + 1)
            return

    print(surface_cnt)


def main():
    T = int(input())
    for _ in range(T):
        solve()


main()
