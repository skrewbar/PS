a = gets.to_f
m, n = gets.split.map &:to_i

p [[m / a, n].max, [n / a, m].max, [m, n].min / a * 2].min