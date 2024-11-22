from random import shuffle

a: int
b: int

candidates = list(range(1, 10001))

shuffle(candidates)
for i in list(candidates):
    print(f"? A {i}", flush=True)
    if int(input()):
        a = i
        break

shuffle(candidates)
for i in candidates:
    print(f"? B {i}", flush=True)
    if int(input()):
        b = i
        break

print(f"! {a + b}")
