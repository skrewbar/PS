WHITE = 0
RED = 1
BLUE = 2


class Direction:
    delta = [0, 0, -1, 1]

    def __init__(self, idx: int):
        self.idx = idx

    @property
    def dx(self):
        return self.delta[self.idx]

    @property
    def dy(self):
        return self.delta[3 - self.idx]

    def reverse(self):
        self.idx ^= 1


class Piece:
    def __init__(self, pos: tuple[int, int], direction: Direction):
        self.pos = pos
        self.direction = direction


def solve():
    N, K = map(int, input().split())

    board = [list(map(int, input().split())) for _ in range(N)]
    pieceStack: list[list[list[int]]] = [[[] for _ in range(N)] for _ in range(N)]
    pieces: list[Piece] = []

    for i in range(K):
        r, c, d = map(lambda x: int(x) - 1, input().split())
        pieces.append(Piece((r, c), Direction(d)))

        pieceStack[r][c].append(i)

    turn = 1
    while turn <= 1000:

        for i in range(K):
            piece = pieces[i]
            r, c = piece.pos
            direction = piece.direction

            nr = r + direction.dx
            nc = c + direction.dy

            if not (0 <= nr < N and 0 <= nc < N) or board[nr][nc] == BLUE:
                direction.reverse()
                nr = r + direction.dx
                nc = c + direction.dy

                if not (0 <= nr < N and 0 <= nc < N) or board[nr][nc] == BLUE:
                    continue

            idx = pieceStack[r][c].index(i)
            movingPieceNums = pieceStack[r][c][idx:]
            del pieceStack[r][c][idx:]

            if board[nr][nc] == RED:
                movingPieceNums.reverse()

            pieceStack[nr][nc].extend(movingPieceNums)

            for p in pieceStack[nr][nc]:
                pieces[p].pos = (nr, nc)

            if len(pieceStack[nr][nc]) >= 4:
                print(turn)
                return

        turn += 1

    print(-1)


solve()
