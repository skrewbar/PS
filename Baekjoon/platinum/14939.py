from copy import deepcopy


def charToBool(char: str):
    if char == "O":
        return 1
    else:
        return 0


original_bulbs = [list(map(charToBool, input())) for i in range(10)]


def turn(x, y, bulbs):
    if bulbs[x][y] == 1:
        bulbs[x][y] = 0
    else:
        bulbs[x][y] = 1

    if x - 1 >= 0:
        if bulbs[x - 1][y] == 1:
            bulbs[x - 1][y] = 0
        else:
            bulbs[x - 1][y] = 1

    if y - 1 >= 0:
        if bulbs[x][y - 1] == 1:
            bulbs[x][y - 1] = 0
        else:
            bulbs[x][y - 1] = 1

    if x < 9:
        if bulbs[x + 1][y] == 1:
            bulbs[x + 1][y] = 0
        else:
            bulbs[x + 1][y] = 1

    if y < 9:
        if bulbs[x][y + 1] == 1:
            bulbs[x][y + 1] = 0
        else:
            bulbs[x][y + 1] = 1


def printBoard(bulbs):
    for x in range(10):
        print(bulbs[x])


min_count = -1
for a in range(2):  # 1
    for b in range(2):  # 2
        for c in range(2):  # 3
            for d in range(2):  # 4
                for e in range(2):  # 5
                    for f in range(2):  # 6
                        for g in range(2):  # 7
                            for h in range(2):  # 8
                                for i in range(2):  # 9
                                    for j in range(2):  # 10
                                        press_count = 0
                                        press_list = [a, b, c, d, e, f, g, h, i, j]
                                        bulbs = deepcopy(original_bulbs)

                                        # debug = False
                                        # if press_list == [1, 0, 1, 0, 0, 0, 0, 1, 0, 1]:
                                        #     debug = True

                                        for p in range(10):
                                            if press_list[p] == 1:
                                                turn(0, p, bulbs)
                                                press_count += 1

                                        for x in range(1, 10):
                                            for y in range(10):
                                                if bulbs[x - 1][y] == 1:
                                                    # if debug:
                                                    #     printBoard(bulbs)
                                                    #     print(x, y)
                                                    turn(x, y, bulbs)
                                                    press_count += 1

                                        success = True
                                        for x in range(10):
                                            for y in range(10):
                                                if (success) and (bulbs[x][y] == 1):
                                                    success = False
                                                    break

                                        if success:
                                            if min_count == -1:
                                                min_count = press_count
                                                # print(press_list)
                                            else:
                                                min_count = min(min_count, press_count)
                                                # if min_count == press_count:
                                                #     print(press_list)
print(min_count)
