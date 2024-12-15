from random import randint
from pathlib import Path


with open(Path(__file__).parent / ".INPUT", "w") as f:
    n = randint(1, 100)
    f.write(f"{n}\n")
    arr = [str(randint(1, 100)) for _ in range(n)]
    f.write(f"{" ".join(arr)}\n")

    m = randint(1, 100)
    f.write(f"{m}\n")
    for _ in range(m):
        query = randint(1, 6)
        l = randint(1, n)
        r = randint(l, n)
        f.write(f"{query} {l} {r}")
        if query <= 3:
            f.write(f" {randint(1, 10)}")
        f.write("\n")
