import sys

input = lambda: sys.stdin.readline().rstrip()


MOD = int(1e9) + 7


class Command:
    def __init__(self, s: str) -> None:
        self.operator = s[0]
        self.number = int(s[1:])

    def __call__(self, K: int) -> int:
        match self.operator:
            case "+":
                return K + self.number
            case "*":
                return K * self.number
            case _:
                return K - self.number


def main():
    N, K = map(int, input().split())

    big_enough = False
    for _ in range(N):
        c1, c2 = map(Command, input().split())

        if not big_enough:
            K = max(c1(K), c2(K))
        else:
            # "*" < "+" < "-"
            if c1.operator > c2.operator:
                c1, c2 = c2, c1

            if c1.operator != c2.operator:
                if c1.operator == "*" and c1.number == 0:
                    K = c2(K)
                elif c2.operator == "-":
                    K = c1(K)
                elif c1.number > 1:  # c1.operator == "*"
                    K = c1(K)
                else:
                    K = c2(K)
            else:
                if c1.operator == "-":
                    c = max(c1, c2, key=lambda c: -c.number)
                else:
                    c = max(c1, c2, key=lambda c: c.number)

                    if c.operator == "*" and c.number == 0:
                        big_enough = False

                K = c(K)

        if K >= int(1e20):
            big_enough = True

        if big_enough:
            K %= MOD
        elif K < 0:
            K = 0

    print(K % MOD)


main()
