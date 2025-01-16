for _ in range(int(input())):
    x1, y1, x2, y2 = map(int, input().split())
    n = int(input())
    planet_sys = [tuple(map(int, input().split())) for _ in range(n)]
    count = 0

    for cx, cy, r in planet_sys:
        is_departure_in = False

        squared_dist_depart = (cx - x1) ** 2 + (cy - y1) ** 2
        if squared_dist_depart <= r**2:
            count += 1
            is_departure_in = True

        squared_dist_arrival = (cx - x2) ** 2 + (cy - y2) ** 2
        if squared_dist_arrival <= r**2:
            count += -1 if is_departure_in else 1
    print(count)
