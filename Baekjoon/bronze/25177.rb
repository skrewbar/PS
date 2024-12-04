n, m = gets.split.map &:to_i
now = gets.split.map &:to_i
past = gets.split.map &:to_i

max = 0
for i in 0...past.length
  if i < n
    max = [past[i] - now[i], max].max
  else
    max = [past[i], max].max
  end
end

p max