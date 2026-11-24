n = gets.to_i
res = gets.split.map &:to_i

score = 0
streak = 0
res.each_with_index do |value, index|
  if value == 0
    streak = 0
  else
    streak += 1
    score += streak
  end
end

p score