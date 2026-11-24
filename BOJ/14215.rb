a, b, c = gets.split.map(&:to_i).sort
c -= 1 while a + b <= c
p a + b + c