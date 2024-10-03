numberOfPeople = [[0 for i in range(15)] for i in range(15)]


def getNumberOfPeople(floor: int, unit: int) -> int:
    if floor == 0:
        return unit
    else:
        if numberOfPeople[floor][unit] != 0:
            return numberOfPeople[floor][unit]
        else:
            sum_ = 0
            for i in range(1, unit + 1):
                sum_ += getNumberOfPeople(floor - 1, i)
            numberOfPeople[floor][unit] = sum_
            return sum_


for _ in range(int(input())):
    k = int(input())
    n = int(input())
    print(getNumberOfPeople(k, n))
