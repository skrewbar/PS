a: int
b: int

for i in range(1, 10):
    print(f"? A {i}", flush=True)
    if int(input()):
        a = i
        break

for i in range(1, 10):
    print(f"? B {i}", flush=True)
    if int(input()):
        b = i
        break

print(f"! {a + b}")
