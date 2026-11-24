N = input()
haystack = {i for i in input().split()}
M = input()

for num in input().split():
    if num in haystack:
        print(1)
    else:
        print(0)
