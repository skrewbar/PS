VERTICAL = "|"
HORIZONTAL = "-"
character = {"U": VERTICAL, "D": VERTICAL, "L": HORIZONTAL, "R": HORIZONTAL}


def main():
    N = int(input())
    moves = input()

    grid = [["."] * N for _ in range(N)]
    r, c = 0, 0
    for i in range(len(moves)):
        nr, nc = r, c

        match moves[i]:
            case "U":
                nr -= 1
            case "D":
                nr += 1
            case "L":
                nc -= 1
            case "R":
                nc += 1
        
        if nr < 0 or nr >= N or nc < 0 or nc >= N:
            continue

        if grid[r][c] != "." and grid[r][c] != character[moves[i]]:
            grid[r][c] = "+"
        else:
            grid[r][c] = character[moves[i]]

        r, c = nr, nc

        if grid[r][c] != "." and grid[r][c] != character[moves[i]]:
            grid[r][c] = "+"
        else:
            grid[r][c] = character[moves[i]]


    for row in grid:
        print(*row, sep="")


main()
