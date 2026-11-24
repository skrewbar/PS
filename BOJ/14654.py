SCISSORS = 1
ROCK = 2
PAPER = 3

n = int(input())

namja = list(map(int, input().split()))
newyork = list(map(int, input().split()))

max_streak = 0
streak = 0
streakTeam = 1


def getwinner(a, b):
    """-1이면 무승부, 0이면 왼쪽 승리, 1이면 오른쪽 승리"""
    if a == b:
        return -1

    if a == SCISSORS and b == PAPER:
        return 0
    if a == ROCK and b == SCISSORS:
        return 0
    if a == PAPER and b == ROCK:
        return 0

    return 1


for i in range(n):
    winner = getwinner(namja[i], newyork[i])

    if winner == streakTeam:
        streak += 1
    else:
        streakTeam ^= 1
        streak = 1
    max_streak = max(streak, max_streak)

print(max_streak)
