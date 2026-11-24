from functools import cmp_to_key

input()
print(
    int(
        "".join(
            sorted(
                input().split(),
                key=cmp_to_key(lambda a, b: 1 if int(a + b) < int(b + a) else -1),
            )
        )
    )
)
