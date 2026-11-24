a1, a0 = gets.split.map &:to_i
c = gets.to_i
n0 = gets.to_i

if a1 - c > 0
  p 0
elsif a1 - c == 0 and a0 <= 0
  p 1
elsif a1 * n0 + a0 <= c * n0
  p 1
else
  p 0
end