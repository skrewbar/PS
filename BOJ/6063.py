sides = tuple(range(6))
L, F, R, B, U, D = sides


def swap_column(
    side1: list[list],
    col1: int,
    side2: list[list],
    col2: int,
    *,
    reversed: bool = False,
) -> None:
    if not reversed:
        for row in range(3):
            side1[row][col1], side2[row][col2] = side2[row][col2], side1[row][col1]
    else:
        for row in range(3):
            side1[row][col1], side2[2 - row][col2] = (
                side2[2 - row][col2],
                side1[row][col1],
            )


def swap_row(
    side1: list[list],
    row1: int,
    side2: list[list],
    row2: int,
    *,
    reversed: bool = False,
) -> None:
    if not reversed:
        for col in range(3):
            side1[row1][col], side2[row2][col] = side2[row2][col], side1[row1][col]
    else:
        for col in range(3):
            side1[row1][col], side2[row2][2 - col] = (
                side2[row2][2 - col],
                side1[row1][col],
            )


def swap_row_column(
    side1: list[list], row: int, side2: list[list], col: int, *, reversed: bool = False
) -> None:
    if not reversed:
        for i in range(3):
            side1[row][i], side2[i][col] = side2[i][col], side1[row][i]
    else:
        for i in range(3):
            side1[row][i], side2[2 - i][col] = side2[2 - i][col], side1[row][i]


def swap_column_row(
    side1: list[list], col: int, side2: list[list], row: int, *, reversed: bool = False
) -> None:
    swap_row_column(side2, row, side1, col, reversed=reversed)


def turn_side_clockwise(side: list[list]) -> None:
    # swap edges counterclockwise beginning with the right piece
    side[1][2], side[0][1] = side[0][1], side[1][2]
    side[0][1], side[1][0] = side[1][0], side[0][1]
    side[1][0], side[2][1] = side[2][1], side[1][0]

    # swap corners counterclockwise beginning with the top right piece
    side[0][2], side[0][0] = side[0][0], side[0][2]
    side[0][0], side[2][0] = side[2][0], side[0][0]
    side[2][0], side[2][2] = side[2][2], side[2][0]


class Cube:
    c: list[list[list[str]]]

    def __init__(self):
        self.c = [[[""] * 3 for _ in range(3)] for _ in range(6)]

        self.c[U] = [input().strip().split() for _ in range(3)]

        for i in range(3):
            line = input().split()
            self.c[L][i] = line[0:3]
            self.c[F][i] = line[3:6]
            self.c[R][i] = line[6:9]
            self.c[B][i] = line[9:12]

        self.c[D] = [input().strip().split() for _ in range(3)]

    def L(self):
        swap_column(self.c[F], 0, self.c[U], 0)
        swap_column(self.c[U], 0, self.c[B], 2, reversed=True)
        swap_column(self.c[B], 2, self.c[D], 0, reversed=True)
        turn_side_clockwise(self.c[L])

    def F(self):
        swap_row_column(self.c[U], 2, self.c[L], 2, reversed=True)
        swap_column_row(self.c[L], 2, self.c[D], 0)
        swap_row_column(self.c[D], 0, self.c[R], 0, reversed=True)
        turn_side_clockwise(self.c[F])

    def R(self):
        swap_column(self.c[U], 2, self.c[F], 2)
        swap_column(self.c[F], 2, self.c[D], 2)
        swap_column(self.c[D], 2, self.c[B], 0, reversed=True)
        turn_side_clockwise(self.c[R])

    def B(self):
        swap_row_column(self.c[U], 0, self.c[R], 2)
        swap_column_row(self.c[R], 2, self.c[D], 2, reversed=True)
        swap_row_column(self.c[D], 2, self.c[L], 0)
        turn_side_clockwise(self.c[B])

    def U(self):
        swap_row(self.c[F], 0, self.c[R], 0)
        swap_row(self.c[R], 0, self.c[B], 0)
        swap_row(self.c[B], 0, self.c[L], 0)
        turn_side_clockwise(self.c[U])

    def D(self):
        swap_row(self.c[F], 2, self.c[L], 2)
        swap_row(self.c[L], 2, self.c[B], 2)
        swap_row(self.c[B], 2, self.c[R], 2)
        turn_side_clockwise(self.c[D])


def solve(tc: int):
    cube = Cube()

    rotate_cnt = int(input())
    for _ in range(rotate_cnt):
        side, direction = map(int, input().split())
        direction %= 4

        for _ in range(direction):
            match side:
                case 0:
                    cube.L()
                case 1:
                    cube.F()
                case 2:
                    cube.R()
                case 3:
                    cube.B()
                case 4:
                    cube.U()
                case 5:
                    cube.D()

    print(f"Scenario #{tc}:")
    for i in range(3):
        print(" " * 5, *cube.c[U][i])
    for i in range(3):
        print(*cube.c[L][i], *cube.c[F][i], *cube.c[R][i], *cube.c[B][i])
    for i in range(3):
        print(" " * 5, *cube.c[D][i])
    print()


for tc in range(1, int(input()) + 1):
    solve(tc)
