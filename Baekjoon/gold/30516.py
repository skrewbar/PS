from typing import NamedTuple


class Bundle(NamedTuple):
    number: int
    elements: tuple[int, ...]


def main():
    N = int(input())
    a = list(map(int, input().split()))

    if N == 2 and a[0] != 0 and a[0] == a[1]:
        print(-1)
        return

    bundles: list[Bundle] = []

    end = -1
    for i in range(N - 1):
        if a[i] != 0 and a[i] == a[i + 1]:
            bundles.append(Bundle(len(bundles) + 1, tuple(a[end + 1 : i + 1])))
            end = i
    bundles.append(Bundle(len(bundles) + 1, tuple(a[end + 1 : N])))

    if (
        len(bundles) == 2
        and bundles[0].elements[0] != 0
        and bundles[0].elements[0] == bundles[-1].elements[-1]
    ):
        bundles.append(Bundle(2, bundles[-1].elements[:-1]))
        bundles[-2] = Bundle(3, (a[-1],))
    else:
        bundles.reverse()

    print(len(bundles))
    length = [0] * (len(bundles) + 1)
    for bundle in bundles:
        length[bundle.number] = len(bundle.elements)
    for i in range(1, len(bundles) + 1):
        print(length[i], end=" ")
    print()
    for bundle in bundles:
        print(bundle.number, end=" ")


main()
