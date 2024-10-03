N, r, c = map(int, input().split())

answer = 0

while N != 0:
    N -= 1

    if (r < 2 ** N) and (c < 2 ** N): # 왼쪽 위
        continue
    if (r < 2**N) and (c >= 2**N):  # 오른쪽 위
        answer += (2**N) * (2**N) * 1
        c -= 2**N
    elif (r >= 2**N) and (c < 2**N):  # 왼쪽 밑
        answer += (2**N) * (2**N) * 2
        r -= 2**N
    else:  # 오른쪽 밑
        answer += (2**N) * (2**N) * 3
        r -= 2**N
        c -= 2**N

print(answer)
