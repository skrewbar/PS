import re

def main():
    S = input()

    if re.fullmatch("(100+1+|01)+", S) is not None:
        print("SUBMARINE")
    else:
        print("NOISE")


main()
