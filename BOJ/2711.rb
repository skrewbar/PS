t = gets.to_i

t.times do
  pos, str = gets.chomp.split
  pos = pos.to_i - 1

  str.chars.each_with_index do |c, i|
    print c if i != pos
  end
  puts
end