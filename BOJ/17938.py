n = int(input())
p, t = map(int, input().split())

p -= 1
start = -1
raiseCount = 1
isDecreasing = False

for _ in range(t - 1):
    start += raiseCount
    start %= n << 1

    if isDecreasing:
        raiseCount -= 1
        if raiseCount == 1:
            isDecreasing = False
    else:
        raiseCount += 1
        if raiseCount == n << 1:
            isDecreasing = True


end = start + raiseCount
start += 1

if start >= (n << 1) - 1:
    start %= n << 1
    end %= n << 1

start >>= 1
end >>= 1

if start <= p <= end or p + n <= end:
    print("Dehet YeonJwaJe ^~^")
else:
    print("Hing...NoJam")
