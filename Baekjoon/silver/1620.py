import sys

input = lambda: sys.stdin.readline().rstrip()

N, M = map(int, input().split())

pokemons = {}
for i in range(1, N + 1):
    name = input()
    pokemons[i] = name
    pokemons[name] = i

for i in range(M):
    quiz = input()
    try:
        quiz = int(quiz)  # 만약 quiz가 정수이면
    except ValueError:
        pass
    finally:
        print(pokemons[quiz])
