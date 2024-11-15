x = gets.to_i

n = 1
n += 1 while n * (n + 1) / 2 < x
x -= n * (n - 1) / 2 + 1

row = nil
column = nil

if n % 2 == 0
  row = 1
  column = n
  x.times do
    row += 1
    column -= 1
  end
else
  row = n
  column = 1
  x.times do
    row -= 1
    column += 1
  end
end

puts "#{row}/#{column}"