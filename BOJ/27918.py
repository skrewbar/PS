N = int(input())
d, p = 0, 0

for _ in range(N):
    if input() == "D":
        d += 1
    else:
        p += 1
    
    if abs(d - p) == 2:
        break
        
print(d, p, sep=":")