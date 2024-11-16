x_set = Set.new
y_set = Set.new

3.times do
  x, y = gets.split.map &:to_i
  if x_set.include? x
    x_set.delete x
  else
    x_set << x
  end
  if y_set.include? y
    y_set.delete y
  else
    y_set << y
  end
end

puts "#{x_set.to_a[0]} #{y_set.to_a[0]}"