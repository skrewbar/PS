gets.to_i.times do
  c = gets.to_i
  quarter = c / 25
  c %= 25

  dime = c / 10
  c %= 10

  nickel = c / 5
  c %= 5

  puts "#{quarter} #{dime} #{nickel} #{c}"
end