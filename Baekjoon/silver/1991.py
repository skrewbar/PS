import sys

input = lambda: sys.stdin.readline().rstrip()

nodeCount = int(input())
ALPHABETS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
child = {i: [] for i in ALPHABETS}

for _ in range(nodeCount):
    root, leftChild, rightChild = input().split()
    child[root] = [leftChild, rightChild]


def preorder(node):
    if node == ".":
        return

    print(node, end="")
    preorder(child[node][0])
    preorder(child[node][1])


def inorder(node):
    if node == ".":
        return

    inorder(child[node][0])
    print(node, end="")
    inorder(child[node][1])


def postorder(node):
    if node == ".":
        return

    postorder(child[node][0])
    postorder(child[node][1])
    print(node, end="")


preorder("A")
print()
inorder("A")
print()
postorder("A")
