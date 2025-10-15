def main():
    length = float(input())
    red = sorted(map(float, input().split()))
    blue = sorted(map(float, input().split()))
    yellow = sorted(map(float, input().split()))

    m = (red[0] + red[1]) / 2
    length = max(m, length - m)

    blue = sorted(map(lambda x: abs(x - m), blue))
    yellow = sorted(map(lambda x: abs(x - m), yellow))

    if blue[0] != blue[1]:
        m = (blue[0] + blue[1]) / 2

        yellow = sorted(map(lambda x: abs(x - m), yellow))
        length = max(m, length - m)

    if yellow[0] != yellow[1]:
        m = (yellow[0] + yellow[1]) / 2
        length = max(m, length - m)

    print(f"{length:.1f}")


main()
