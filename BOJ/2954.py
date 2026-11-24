import re

print(re.sub(r"([aeiou])p[aeiou]", r"\1", input()))
