treeCount, wants = map(int, input().split())
trees = list(map(int, input().split()))


def getTrees(height: int) -> int:
    sum_ = 0
    for tree in trees:
        sum_ += max(tree - height, 0)
    return sum_


left = 0
right = 2_000_000_000
mid = (left + right) // 2
gottenWoods = getTrees(mid)
while (gottenWoods != wants) and (left != mid):
    gottenWoods = getTrees(mid)
    if gottenWoods < wants:
        right = mid
        mid = (left + right) // 2

    elif gottenWoods > wants:
        left = mid
        mid = (left + right) // 2

if getTrees(mid) < wants:
    print(mid - 1)
else:
    print(mid)
