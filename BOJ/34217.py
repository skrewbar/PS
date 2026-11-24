def main():
    A, B = map(int, input().split())
    C, D = map(int, input().split())

    if A + C == B + D:
        print("Either")
    else:
        print("Hanyang Univ." if A + C < B + D else "Yongdap")


main()
