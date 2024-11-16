minx, miny = 10000, 10000
maxx, maxy = -10000, -10000

gets.to_i.times do
  x, y = gets.split.map &:to_i
  minx = [x, minx].min
  miny = [y, miny].min
  maxx = [x, maxx].max
  maxy = [y, maxy].max
end

puts (maxx - minx) * (maxy - miny)