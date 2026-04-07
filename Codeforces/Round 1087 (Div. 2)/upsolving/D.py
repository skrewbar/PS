def solve():
    r, g, b = map(int, input().split())
    rg, rb, gb = 0, 0, 0

    while (r > 0) + (g > 0) + (b > 0) >= 2:
        if r <= g and r <= b:
            gb += 1
            g -= 1
            b -= 1
        elif g <= r and g <= b:
            rb += 1
            r -= 1
            b -= 1
        else:
            rg += 1
            r -= 1
            g -= 1

    if r:
        print("R", end="")
        print("GR" * rg, end="")
        print("BR" * rb, end="")
        print(("BG" if rb else "GB") * gb)
    elif g:
        print("G", end="")
        print("RG" * rg, end="")
        print("BG" * gb, end="")
        print(("BR" if gb else "RB") * rb)
    else:
        if b:
            print("B", end="")
        print("RB" * rb, end="")
        print("GB" * gb, end="")
        print(("GR" if gb else "RG") * rg)


def main():
    for _ in range(int(input())):
        solve()


main()
