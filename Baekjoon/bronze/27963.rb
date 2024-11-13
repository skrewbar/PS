d1, d2, x = gets.split.map &:to_f
d1, d2 = [d1, d2].sort
p 100 / (x / d2 + (100 - x) / d1)