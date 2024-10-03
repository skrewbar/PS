padovan_table = [0, 1, 1, 1, 2, 2]


def padovan(n: int):
    if n <= len(padovan_table) - 1:
        return padovan_table[n]
    else:
        padovan_table.append(padovan(n - 1) + padovan(n - 5))
        return padovan_table[n]


for t in range(int(input())):
    print(padovan(int(input())))
