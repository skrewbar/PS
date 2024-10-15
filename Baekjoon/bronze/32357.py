n = int(input())
strings = [input() for _ in range(n)]

palindrome_count = 0

for s in strings:
    palindrome_count += 1 if s == s[::-1] else 0

print(palindrome_count * (palindrome_count - 1))
