def main():
    LEFT, RIGHT = range(2)

    N = int(input())

    seats = input()
    ans = 0

    holder = LEFT

    i = 0
    while i < len(seats):
        if seats[i] == "S":
            ans += 1
        else:
            if holder == RIGHT:
                ans += 1
            else:
                ans += 2
                holder = RIGHT
            i += 1
        i += 1

    print(ans)


main()
