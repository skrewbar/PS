from typing import Iterable


class Cell:
    def __init__(self, score: int):
        self.score = score
        self.blue = None
        self.red = None

    def connect(self, to: "Cell", scores: Iterable[int], blue: bool = False):
        cells = list(map(Cell, scores))

        if blue:
            self.blue = cells[0]
        else:
            self.red = cells[0]

        for i in range(len(cells) - 1):
            cells[i].red = cells[i + 1]

        cells[-1].red = to


def solve():
    # initialize game board
    start = Cell(0)
    left = Cell(10)
    bottom = Cell(20)
    right = Cell(30)
    top = Cell(40)
    end = Cell(0)
    center = Cell(25)

    start.connect(left, range(2, 8 + 1, 2))
    left.connect(bottom, range(12, 18 + 1, 2))
    bottom.connect(right, range(22, 28 + 1, 2))
    right.connect(top, range(32, 38 + 1, 2))

    left.connect(center, range(13, 19 + 1, 3), True)
    bottom.connect(center, range(22, 24 + 1, 2), True)
    right.connect(center, range(28, 26 - 1, -1), True)

    center.connect(top, range(30, 35 + 1, 5))
    top.red = end

    # solve
    numbers = list(map(int, input().split()))

    def getMaxScore(pos: list[Cell], step: int) -> int:
        if step == 10:
            return 0

        maxScore = 0
        for i in range(4):
            prevPos = pos[i]

            nxt = pos[i].blue if pos[i].blue is not None else pos[i].red
            if nxt is None:
                continue
            pos[i] = nxt

            for _ in range(numbers[step] - 1):
                nxt = pos[i].red

                if nxt is None:
                    break

                pos[i] = nxt

            if pos[i] != end and pos.count(pos[i]) > 1:
                pos[i] = prevPos
                continue

            maxScore = max(maxScore, getMaxScore(pos, step + 1) + pos[i].score)

            pos[i] = prevPos

        return maxScore

    print(getMaxScore([start, start, start, start], 0))


solve()
