for _ in range(int(input())):
    n = int(input())

    clothes = {}
    for i in range(n):
        cloth = input().split()
        if cloth[1] in clothes:
            clothes[cloth[1]].add(cloth[0])
        else:
            clothes[cloth[1]] = {cloth[0]}

    answer = 1
    for i in clothes:
        answer *= len(clothes[i]) + 1
    answer -= 1

    print(answer)
