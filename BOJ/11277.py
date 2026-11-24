class Bitset:
    def __init__(self, bits: int = 0):
        self.bits = bits

    def __contains__(self, x: int):
        return bool(self.bits & (1 << x))


def main():
    N, M = map(int, input().split())

    consequents: list[tuple[int, int]] = []
    for _ in range(M):
        i, j = map(int, input().split())
        consequents.append((i, j))

    for comb in map(Bitset, range(1 << N)):
        expression = True

        for i, j in consequents:
            left = (i < 0 and not -i - 1 in comb) or (i > 0 and i - 1 in comb)
            right = (j < 0 and not -j - 1 in comb) or (j > 0 and j - 1 in comb)

            if not left and not right:
                expression = False
                break

        if expression:
            print(1)
            return

    print(0)


main()
