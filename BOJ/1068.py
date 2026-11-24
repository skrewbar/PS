N = int(input())
parent_list = list(map(int, input().split()))
delete_num = int(input())


def dfs(index: int):
    for i in range(len(parent_list)):
        if parent_list[i] == index:
            dfs(i)
    parent_list[index] = -2


def isLeap(index: int):
    if parent_list[index] == -2:
        return False

    for i in range(len(parent_list)):
        if parent_list[i] == index:
            return False
    return True


dfs(delete_num)
answer = 0
for i in range(len(parent_list)):
    if isLeap(i):
        answer += 1

print(answer)
