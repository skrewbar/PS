n = int(input())

print("bowling " * n, flush=True)

inputs = input().split()

for i in inputs:
    print("soccer " if i == "swimming" else "swimming ", end="")
