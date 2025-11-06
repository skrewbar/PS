from dataclasses import dataclass


@dataclass
class Assignment:
    score: int
    time: int


def main():
    N = int(input())

    remains: list[Assignment] = []
    ans = 0

    for _ in range(N):
        info = tuple(map(int, input().split()))

        if info[0] == 1:
            remains.append(Assignment(*info[1:]))

        if remains:
            remains[-1].time -= 1
            if remains[-1].time == 0:
                ans += remains[-1].score
                remains.pop()

    print(ans)


main()
