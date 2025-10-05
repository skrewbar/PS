def solve(memory: list[int]):
    pc = 0
    adder = 0

    while True:
        cmd = memory[pc]
        tp = cmd // (1 << 5)
        address = cmd % (1 << 5)

        pc += 1
        pc %= 1 << 5

        match tp:
            case 0b000:
                memory[address] = adder
            case 0b001:
                adder = memory[address]
            case 0b010:
                if adder == 0:
                    pc = address
            case 0b100:
                adder -= 1
                adder %= 1 << 8
            case 0b101:
                adder += 1
                adder %= 1 << 8
            case 0b110:
                pc = address
            case 0b111:
                print(f"{bin(adder)[2:]:0>8}")
                return


def main():
    while True:
        try:
            memory = [int(input(), 2) for _ in range(32)]
            solve(memory)
        except EOFError:
            return


if __name__ == "__main__":
    main()
