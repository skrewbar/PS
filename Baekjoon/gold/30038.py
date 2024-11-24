class Monster:
    def __inif__(self):
        self.health: int
        self.defense: int
        self.exp: int

    def __eq__(self, string: str) -> bool:
        return string == "m"


class Player:
    def __init__(self):
        self.atk = 5
        self.reach = 1
        self.speed = 1
        self.need_exp = 10
        self.exp = 0
        self.level = 1
        self.cleared = False

        self.dose_count = 0
        self.OVERDOSE = 0  # 0이면 해제 양수면 OVERDOSE
        self.active_point = 0

        self.x: int
        self.y: int

    def behave(self, amount: int):
        self.active_point += amount
        self.OVERDOSE = max(self.OVERDOSE - amount, 0)

    # 순간이동

    def move(self, dx: int, dy: int):  # 각각 -1, 0, 1중 하나
        x = self.x + self.speed * dx
        y = self.y + self.speed * dy
        if x < 0 or n <= x or y < 0 or m <= y:
            return
        square = world[x][y]
        if square == "m" or square == "*":
            return
        self.x = x
        self.y = y
        self.behave(1)

    def up(self):
        self.move(-1, 0)

    def down(self):
        self.move(1, 0)

    def left(self):
        self.move(0, -1)

    def right(self):
        self.move(0, 1)

    # 대기

    def wait(self):
        self.behave(1)

    # 경험치 정산

    def levelup(self):
        while self.need_exp <= self.exp:
            self.exp -= self.need_exp

            self.atk += self.level
            self.reach += 1
            self.need_exp += 10
            self.level += 1

    # 공격

    def attack(self, dx: int, dy: int):  # 각각 -1, 0, 1중 하나
        if self.OVERDOSE:
            return
        self.behave(3)
        x, y = self.x, self.y
        for _ in range(self.reach):
            x += dx
            y += dy
            if world[x][y] == "*":
                break
            if world[x][y] != "m":
                continue
            monster: Monster = world[x][y]
            if self.atk < monster.defense:
                continue
            monster.health -= self.atk - monster.defense
            if monster.health <= 0:
                world[x][y] = "."
                self.exp += monster.exp
        self.levelup()

    def attack_up(self):
        self.attack(-1, 0)

    def attack_down(self):
        self.attack(1, 0)

    def attack_left(self):
        self.attack(0, -1)

    def attack_right(self):
        self.attack(0, 1)

    # 약 먹기

    def dose(self, delta: int):
        if self.OVERDOSE:
            return
        self.behave(2)
        self.dose_count += 1
        self.speed += delta
        self.speed = max(self.speed, 0)

        if self.dose_count == 5:
            self.OVERDOSE = 10
            self.dose_count = 0

    def dose_up(self):
        self.dose(1)

    def dose_down(self):
        self.dose(-1)

    # 클리어

    def clear(self) -> bool:
        if self.OVERDOSE:
            return
        self.cleared = world[self.x][self.y] == "g"


player = Player()

n, m = map(int, input().split())
world = [list(input()) for _ in range(n)]
monsters: list[Monster] = []
for i in range(n):
    for j in range(m):
        if world[i][j] == "m":
            world[i][j] = Monster()
            monsters.append(world[i][j])
        if world[i][j] == "p":
            player.x, player.y = i, j
            world[i][j] = "."

k = int(input())

for i, health in enumerate(map(int, input().split())):
    monsters[i].health = health
for i, defense in enumerate(map(int, input().split())):
    monsters[i].defense = defense
for i, exp in enumerate(map(int, input().split())):
    monsters[i].exp = exp

s = int(input())

for behave in input().split():
    match behave:
        case "u":
            player.up()
        case "d":
            player.down()
        case "l":
            player.left()
        case "r":
            player.right()
        case "w":
            player.wait()
        case "au":
            player.attack_up()
        case "ad":
            player.attack_down()
        case "al":
            player.attack_left()
        case "ar":
            player.attack_right()
        case "du":
            player.dose_up()
        case "dd":
            player.dose_down()
        case "c":
            player.clear()
            if player.cleared:
                break

print(player.level, player.exp)
print(player.active_point)

world[player.x][player.y] = "p"
for i in range(n):
    for j in range(m):
        print("m" if world[i][j] == "m" else world[i][j], end="")
    print()

for monster in monsters:
    if monster.health <= 0:
        continue
    print(monster.health)
