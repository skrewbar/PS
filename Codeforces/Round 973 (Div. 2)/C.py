import sys

input = lambda: sys.stdin.readline().rstrip()

RIGHT = 1
LEFT = 0


for t in range(int(input())):
    n = int(input())

    direction = RIGHT
    answer = [0]

    print("?", *answer)
    sys.stdout.flush()
    i = int(input())

    if i == 0:
        print("!", "1" * n)
        sys.stdout.flush()
        continue

    while len(answer) != n:
        if direction == RIGHT:
            answer.append(0)
            print("? ", *answer, sep="")
            sys.stdout.flush()
            i = int(input())

            if i == 0:
                answer[-1] = 1
                print("? ", *answer, sep="")
                sys.stdout.flush()
                i = int(input())

                if i == 0:
                    direction = LEFT
                    answer.pop()

        else:
            answer.insert(0, 0)
            print("? ", *answer, sep="")
            sys.stdout.flush()
            i = int(input())

            if i == 0:
                answer[0] = 1

    print("! ", *answer, sep="")
    sys.stdout.flush()
