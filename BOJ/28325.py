N = int(input())
rooms = list(map(int, input().split()))
new_rooms = []
cut = 0
answer = 0
for i in range(N):
    if rooms[i] != 0:
        answer += rooms[i]
        new_rooms.append(rooms[cut:i])
        cut = i + 1

if rooms[0] == rooms[N - 1] == 0:
    if cut == 0:
        new_rooms.append(rooms[cut + 1 : N])
    else:
        new_rooms.append(rooms[cut:N] + new_rooms[0])
        new_rooms[0] = []
elif rooms[N - 1] == 0:
    new_rooms.append(rooms[cut:N])
# print(new_rooms, answer)

for room in new_rooms:
    room_count = len(room)
    if room_count % 2 == 0:
        answer += room_count // 2
    else:
        answer += room_count // 2 + 1

print(answer)
