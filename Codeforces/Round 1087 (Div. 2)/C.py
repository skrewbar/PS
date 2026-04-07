def solve():
    n = int(input())

    for i in range(1, n):
        print(f"? {2*i + 1} {2*i + 2}", flush=True)

        if int(input()):
            print(f"! {2*i + 1}", flush=True)
            return

    print("? 1 3")
    if int(input()):
        print("! 1", flush=True)
        return

    print("? 1 4")
    if int(input()):
        print("! 1", flush=True)
        return

    print("! 2", flush=True)


def main():
    for _ in range(int(input())):
        solve()


main()
