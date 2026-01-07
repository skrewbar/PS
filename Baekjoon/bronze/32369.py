def main():
    praised = 1
    blamed = 1

    N, A, B = map(int, input().split())
    for _ in range(N):
        praised += A
        blamed += B

        if praised < blamed:
            praised, blamed = blamed, praised
        if praised == blamed:
            blamed -= 1
    
    print(praised, blamed)


main()
