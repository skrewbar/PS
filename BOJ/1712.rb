a, b, c = gets.split.map &:to_f

if c <= b
  p -1
else
  p (a / (c - b) + 0.5).round
end