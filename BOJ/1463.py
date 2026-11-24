n = int(input())
memo = [0 for _ in range(n + 1)]

for i in range(2, n + 1):
    memo[i] = memo[i - 1] + 1

    if i % 3 == 0:
        memo[i] = min(memo[i], memo[i // 3] + 1)

    if i % 2 == 0:
        memo[i] = min(memo[i], memo[i // 2] + 1)

print(memo[n])


"""
위는 신 코드
아래는 구 코드

"""
# n = int(input())
# memo = {n: 0}

# while True:
#     for i in dict(memo):
#         if i == 1:
#             print(memo[i])
#             break

#         if i % 3 == 0:
#             if i // 3 in memo:
#                 memo[i // 3] = min(memo[i // 3], memo[i] + 1)
#             else:
#                 memo[i // 3] = memo[i] + 1

#         if i % 2 == 0:
#             if i // 2 in memo:
#                 memo[i // 2] = min(memo[i // 2], memo[i] + 1)
#             else:
#                 memo[i // 2] = memo[i] + 1

#         if i - 1 in memo:
#             memo[i - 1] = min(memo[i - 1], memo[i] + 1)
#         else:
#             memo[i - 1] = memo[i] + 1
#     if i == 1:
#         break
