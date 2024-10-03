paperNumber = int(input())
papers = [tuple(map(int, input().split())) for i in range(paperNumber)]
drawingPaper = [[0 for i in range(100)] for i in range(100)]

for paper in papers:
    for i in range(paper[0]-1, paper[0]+9):
        for j in range(paper[1]-1, paper[1]+9):
            drawingPaper[i][j] = 1

s = 0
for i in range(100):
    for j in range(100):
        if drawingPaper[i][j] == 1:
            s += 1

print(s)
