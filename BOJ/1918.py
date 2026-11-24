import sys

input = lambda: sys.stdin.readline().rstrip()

stack = []

expression = input()

priority = {"(": 3, "*": 2, "/": 2, "+": 1, "-": 1}

for char in expression:
    if "A" <= char <= "Z":
        print(char, end="")

    elif len(stack) == 0:
        stack.append(char)

    elif char == ")":
        while len(stack) > 0 and stack[-1] != "(":
            print(stack.pop(), end="")
        stack.pop()

    elif priority[char] > priority[stack[-1]]:
        stack.append(char)

    elif priority[char] <= priority[stack[-1]]:
        while len(stack) > 0 and priority[char] <= priority[stack[-1]] and stack[-1] != "(":
            print(stack.pop(), end="")
        stack.append(char)

while stack:
    print(stack.pop(), end="")