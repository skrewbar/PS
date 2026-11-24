sides = tuple(range(6))
initial_color = ("w", "y", "r", "o", "g", "b")
U, D, F, B, L, R = range(6)


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
    """
    U는 U를 앞으로 하고 F을 밑으로 했을 때 기준으로 배치
    F는 U를 위로하고 F를 앞으로 했을 때 기준으로 배치
    L은 U를 위로하고 L을 앞으로 했을 때 기준으로 배치

    나머지는 서로 좌우반전
    """

    c: list[list[list[str]]]

    def __init__(self):
        self.c = [[[""] * 3 for _ in range(3)] for _ in range(6)]

        for side in sides:
            for i in range(3):
                for j in range(3):
                    self.c[side][i][j] = initial_color[side]

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

    def F(self):
        swap_row_column(self.c[U], 2, self.c[L], 2, reversed=True)
        swap_column_row(self.c[L], 2, self.c[D], 2, reversed=True)
        swap_row_column(self.c[D], 2, self.c[R], 0)
        turn_side_clockwise(self.c[F])

    def B(self):
        swap_row_column(self.c[U], 0, self.c[R], 2)
        swap_column_row(self.c[R], 2, self.c[D], 0)
        swap_row_column(self.c[D], 0, self.c[L], 0, reversed=True)
        turn_side_clockwise(self.c[B])

    def L(self):
        swap_column(self.c[U], 0, self.c[B], 2, reversed=True)
        swap_column(self.c[B], 2, self.c[D], 2)
        swap_column(self.c[D], 2, self.c[F], 0, reversed=True)
        turn_side_clockwise(self.c[L])

    def R(self):
        swap_column(self.c[U], 2, self.c[F], 2)
        swap_column(self.c[F], 2, self.c[D], 0, reversed=True)
        swap_column(self.c[D], 0, self.c[B], 0)
        turn_side_clockwise(self.c[R])


# cube = Cube()
# cube.R()

# print(*cube.c[U], sep="\n")


def solve():
    input()
    cube = Cube()

    for rotate in input().split():
        for _ in range(3 if rotate[1] == "-" else 1):
            match rotate[0]:
                case "U":
                    cube.U()
                case "D":
                    cube.D()
                case "F":
                    cube.F()
                case "B":
                    cube.B()
                case "L":
                    cube.L()
                case "R":
                    cube.R()

    for i in cube.c[U]:
        print(*i, sep="")


for _ in range(int(input())):
    solve()
