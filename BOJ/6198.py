n = int(input())

stack = [0]
answer = 0

for _ in range(n):
    h = int(input())

    while len(stack) > 0 and stack[-1] <= h:
        stack.pop()

    answer += len(stack)
    stack.append(h)

print(answer)
