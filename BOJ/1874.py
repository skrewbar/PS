n = int(input())

stack = [0]
inputList = [i for i in range(n, 0, -1)]

ioList = []
try:
    for i in range(n):
        m = int(input())
        while stack[-1] != m:
            stack.append(inputList.pop())
            ioList.append("+")
        stack.pop()
        ioList.append("-")
except:
    print("NO")
else:
    print(*ioList, sep="\n")