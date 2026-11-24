def solve():
    N, X = map(int, input().split())

    # preprocesses powers of 2
    pattyOfLv = [0] * (N + 1)
    pattyOfLv[0] = 1
    for i in range(1, N + 1):
        pattyOfLv[i] = pattyOfLv[i - 1] << 1 | 1

    layerOfLv = [0] * (N + 1)
    layerOfLv[0] = 1
    for i in range(1, N + 1):
        layerOfLv[i] = (layerOfLv[i - 1] << 1) + 3

    def getPattyCnt(level: int, layer: int) -> int:
        if layer <= 0:
            return 0
        if level == 0:
            return 1

        ret = 0

        layer -= 1

        if layer >= layerOfLv[level - 1]:
            ret += pattyOfLv[level - 1]
            layer -= layerOfLv[level - 1]
        else:
            return ret + getPattyCnt(level - 1, layer)

        if layer <= 0:
            return ret

        ret += 1
        layer -= 1

        if layer >= layerOfLv[level - 1]:
            ret += pattyOfLv[level - 1]
        else:
            return ret + getPattyCnt(level - 1, layer)

        return ret

    print(getPattyCnt(N, X))


solve()
