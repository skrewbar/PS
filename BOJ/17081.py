from typing import Any
from math import floor
from dataclasses import dataclass

Empty = "."
Wall = "#"

KILL = "KILL"
DEAD = "DEAD"

HR = "HR"  # 전투에서 승리할 때마다 체력을 3 회복한다. 체력은 최대 체력 수치까지만 회복된다.
RE = "RE"  # 주인공이 사망했을 때 소멸하며, 주인공을 최대 체력으로 부활시켜 준 뒤, 주인공을 첫 시작 위치로 돌려보낸다. 레벨이나 장비 등의 다른 정보는 변함이 없다. 전투 중이던 몬스터가 있다면 해당 몬스터의 체력도 최대치로 회복된다. 소멸한 뒤에 다시 이 장신구를 얻는다면 또 착용한다.
CO = "CO"  # 모든 전투에서, 첫 번째 공격에서 주인공의 공격력(무기 합산)이 두 배로 적용된다. 즉, 모든 첫 공격에서 몬스터에게 max(1, 공격력×2 – 몬스터의 방어력)만큼의 데미지를 입힌다.
EX = "EX"  # 얻는 경험치가 1.2배가 된다. 소수점 아래는 버린다.
DX = "DX"  # 가시 함정에 입는 데미지가 1로 고정되며, Courage 장신구와 함께 착용할 경우, Courage의 공격력 효과가 두 배로 적용되는 대신 세 배로 적용된다.
HU = "HU"  # 보스 몬스터와 전투에 돌입하는 순간 체력을 최대치까지 회복하고, 보스 몬스터의 첫 공격에 0의 데미지를 입는다.
CU = "CU"  # 아무 능력이 없으며, 그냥 장신구 한 자리를 차지한다.

U = (-1, 0)
D = (1, 0)
L = (0, -1)
R = (0, 1)


class Item:
    def __str__(self):
        return "B"


@dataclass
class Weapon(Item):
    attack: int


@dataclass
class Armor(Item):
    defend: int


@dataclass
class Accessory(Item):
    effect: str


class Ending:
    def __init__(self, msg: str = "Press any key to continue."):
        self.msg = msg

    def __str__(self):
        return self.msg


class WinEnding(Ending):
    def __init__(self):
        self.msg = "YOU WIN!"


class DeadEnding(Ending):
    def __init__(self, name: str):
        self.msg = f"YOU HAVE BEEN KILLED BY {name}.."


class Spike:
    name = "SPIKE TRAP"

    def __str__(self):
        return "^"


class Monster:
    def __init__(self, name: str, attack: int, defend: int, max_health: int, exp: int):
        self.name = name
        self.attack = attack
        self.defend = defend
        self.max_health = max_health
        self.hp = max_health
        self.exp = exp

    def __str__(self) -> str:
        return "&"


class Boss(Monster):
    def __str__(self):
        return "M"


class Player:
    def __init__(self):
        self.max_health = 20
        self.hp = 20
        self.base_atk = 2
        self.base_def = 2

        self.level = 1
        self.exp = 0

        self.weapon = 0
        self.armor = 0
        self.accessories: set[str] = set()

    def add_exp(self, exp: int):
        self.exp += floor(exp * 1.2) if EX in self.accessories else exp
        if self.exp >= self.level * 5:
            self.max_health += 5
            self.base_atk += 2
            self.base_def += 2
            self.hp = self.max_health

            self.level += 1
            self.exp = 0

    def first_attack(self, monster: Monster):
        atk = self.base_atk + self.weapon
        if CO in self.accessories:
            if DX in self.accessories:
                atk *= 3
            else:
                atk *= 2

        monster.hp -= max(1, atk - monster.defend)

    @property
    def attack(self):
        return self.base_atk + self.weapon

    @property
    def defend(self):
        return self.base_def + self.armor

    def fight_against_monster(self, monster: Monster):
        monster.hp = monster.max_health

        self.first_attack(monster)
        if monster.hp > 0:
            if isinstance(monster, Boss) and HU in self.accessories:
                self.hp = self.max_health
            else:
                self.hp -= max(1, monster.attack - self.defend)

        is_player_turn = True
        while self.hp > 0 and monster.hp > 0:
            if is_player_turn:
                monster.hp -= max(1, self.attack - monster.defend)
            else:
                self.hp -= max(1, monster.attack - self.defend)

            is_player_turn = not is_player_turn

        if self.hp <= 0:
            if RE in self.accessories:
                self.accessories.remove(RE)
                self.hp = self.max_health
                return RE
            else:
                return DEAD
        else:
            self.add_exp(monster.exp)
            return KILL

    def __str__(self):
        return "@"


class Game:
    def __init__(self):
        n, m = map(int, input().split())
        self.n, self.m = n, m
        self.grid: list[list[Any]] = [list(input()) for _ in range(n)]
        self.start_pos: tuple[int, int]

        moves = input()
        self.moves = [(0, 0) for _ in range(len(moves))]
        for i, move in enumerate(moves):
            if move == "U":
                self.moves[i] = U
            if move == "D":
                self.moves[i] = D
            if move == "L":
                self.moves[i] = L
            if move == "R":
                self.moves[i] = R

        k = 0
        l = 0
        boss_coord = (0, 0)
        for i in range(n):
            for j in range(m):
                if self.grid[i][j] == "B":
                    l += 1
                if self.grid[i][j] == "@":
                    self.start_pos = (i, j)
                    self.grid[i][j] = Empty
                if self.grid[i][j] == "^":
                    self.grid[i][j] = Spike()
                if self.grid[i][j] == "&":
                    k += 1
                if self.grid[i][j] == "M":
                    k += 1
                    boss_coord = (i, j)

        for _ in range(k):
            r, c, s, w, a, h, e = input().split()
            r = int(r) - 1
            c = int(c) - 1
            w = int(w)
            a = int(a)
            h = int(h)
            e = int(e)

            if (r, c) == boss_coord:
                self.grid[r][c] = Boss(s, w, a, h, e)
            else:
                self.grid[r][c] = Monster(s, w, a, h, e)

        for _ in range(l):
            r, c, t, s = input().split()
            r = int(r) - 1
            c = int(c) - 1
            if t == "W":
                self.grid[r][c] = Weapon(int(s))
            if t == "A":
                self.grid[r][c] = Armor(int(s))
            if t == "O":
                self.grid[r][c] = Accessory(s)

        self.player = Player()
        self.turn = 0

    def play(self) -> Ending:
        ending = Ending()
        player = self.player

        pos = list(self.start_pos)
        for move in self.moves:
            # self.print_board(tuple(pos))
            self.turn += 1

            dx, dy = move
            nx = pos[0] + dx
            ny = pos[1] + dy

            if not (0 <= nx < self.n and 0 <= ny < self.m) or self.grid[nx][ny] == Wall:
                nx, ny = pos

            grid = self.grid[nx][ny]

            pos = (nx, ny)
            if grid == Empty:
                continue

            if isinstance(grid, Item):
                self.grid[nx][ny] = Empty

                if isinstance(grid, Weapon):
                    player.weapon = grid.attack
                if isinstance(grid, Armor):
                    player.armor = grid.defend
                if isinstance(grid, Accessory):
                    if len(player.accessories) < 4:
                        player.accessories.add(grid.effect)

            if isinstance(grid, Spike):
                player.hp -= 1 if DX in player.accessories else 5
                if player.hp <= 0:
                    if RE in player.accessories:
                        player.accessories.remove(RE)
                        player.hp = player.max_health
                        pos = self.start_pos
                    else:
                        return DeadEnding(grid.name)

            if isinstance(grid, Monster):
                res = player.fight_against_monster(grid)

                if res == RE:
                    pos = self.start_pos
                if res == DEAD:
                    ending = DeadEnding(grid.name)
                    break
                if res == KILL:
                    self.grid[nx][ny] = Empty
                    if HR in player.accessories:
                        player.hp = min(player.hp + 3, player.max_health)
                    if isinstance(grid, Boss):
                        ending = WinEnding()
                        break

        if not isinstance(ending, DeadEnding):
            self.grid[pos[0]][pos[1]] = self.player
        return ending

    def print_result(self, ending: Ending):
        for row in self.grid:
            for i in row:
                print(i, end="")
            print()
        print(f"Passed Turns : {self.turn}")
        player = self.player
        print(f"LV : {player.level}")
        print(f"HP : {max(0, player.hp)}/{player.max_health}")
        print(f"ATT : {player.base_atk}+{player.weapon}")
        print(f"DEF : {player.base_def}+{player.armor}")
        print(f"EXP : {player.exp}/{player.level * 5}")
        print(ending)

    # def print_board(self, playerpos: tuple[int, int]):
    #     for i in range(self.n):
    #         for j in range(self.m):
    #             if (i, j) == playerpos:
    #                 print(self.player, end="")
    #             else:
    #                 print(self.grid[i][j], end="")
    #         print()
    #     print(f"Passed Turns : {self.turn}")
    #     player = self.player
    #     print(f"LV : {player.level}")
    #     print(f"HP : {max(0, player.hp)}/{player.max_health}")
    #     print(f"ATT : {player.base_atk}+{player.weapon}")
    #     print(f"DEF : {player.base_def}+{player.armor}")
    #     print(f"EXP : {player.exp}/{player.level * 5}")
    #     print("=" * 20)


game = Game()
ending = game.play()
game.print_result(ending)
