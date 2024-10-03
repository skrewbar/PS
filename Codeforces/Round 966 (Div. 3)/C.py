def matches(template: list[int], string: str) -> bool:
    if len(template) != len(string):
        return False

    n_to_s = {}
    s_to_n = {}

    for t, s in zip(template, string):
        if not (t in n_to_s or s in s_to_n):
            n_to_s[t] = s
            s_to_n[s] = t
            continue

        if (t not in n_to_s) ^ (s not in s_to_n):
            return False

        if n_to_s[t] != s or s_to_n[s] != t:
            return False

    return True


for t in range(int(input())):
    n = int(input())
    template = list(map(int, input().split()))

    for _ in range(int(input())):
        print("YES") if matches(template, input()) else print("NO")
