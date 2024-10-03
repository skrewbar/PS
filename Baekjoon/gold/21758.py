flower_count = int(input())
flowers = list(map(int, input().split()))  # 벌들은 꽃에서 꿀을 따 온다.

prefix_sum = [0] * (flower_count + 1)
for i in range(flower_count):
    prefix_sum[i + 1] = prefix_sum[i] + flowers[i]


def getPartSum(i: int, j: int) -> int:
    return prefix_sum[j + 1] - prefix_sum[i]


def getHoney(hiveLoc: int, bee2: int = 0) -> int:  # bee2는 끝에 있지 않은 벌
    if hiveLoc == flower_count - 1:  # 벌집이 오른쪽 끝에 있으면
        return (
            getPartSum(1, flower_count - 1)
            - flowers[bee2]
            + getPartSum(bee2 + 1, flower_count - 1)
        )
    elif hiveLoc == 0:  # 벌집이 왼쪽 끝에 있으면
        return getPartSum(0, flower_count - 2) - flowers[bee2] + getPartSum(0, bee2 - 1)
    else:  # 벌집이 중간에 있으면
        return getPartSum(1, hiveLoc) + getPartSum(hiveLoc, flower_count - 2)


max_honey = 0
for i in range(1, flower_count - 1):
    max_honey = max(
        [
            max_honey,
            getHoney(flower_count - 1, i),
            getHoney(0, i),
            getHoney(i),
        ]
    )

print(max_honey)
