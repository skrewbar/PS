"""
이 코드를 통해 만들어지는 테스트 케이스는 w_i > 0인 금광이 존재함을 보장하지 않습니다.
해당 파일과 같은 폴더에 .INPUT파일을 작성해 줍니다.
"""

from random import randint
import pathlib

# n = randint(1, 3000)
n = 100
MAX = int(1e9)

with open(pathlib.Path(__file__).parent / ".INPUT", "w") as f:
    f.write(f"{n}\n")
    for _ in range(n):
        f.write(f"{randint(0, MAX)} {0} {randint(-MAX, MAX)}\n")
