n, x = gets.split.map(&:to_i)
people = gets.split.map(&:to_i).sum

if people % x == 0
    p 1
else
    p 0
end