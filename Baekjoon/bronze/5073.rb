a, b, c = gets.split.map(&:to_i).sort

until a | b | c == 0
  if c >= a + b
    puts "Invalid"
  elsif a == b and b == c
    puts "Equilateral"
  elsif a == b or b == c or c == a
    puts "Isosceles"
  else
    puts "Scalene"
  end
  a, b, c = gets.split.map(&:to_i).sort
end