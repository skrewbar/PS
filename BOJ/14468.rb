alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

s = gets.chomp
ans = 0
for a in alphabets.chars
  count = Hash.new(0)
  
  i = s.index(a) + 1
  while s[i] != a
    count[s[i]] += 1
    i += 1
  end

  ans += count.filter_map { |_, c| c == 1 }.length
end

p ans / 2