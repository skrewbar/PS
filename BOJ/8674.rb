a, b = gets.split.map &:to_i

if a % 2 == 0 or b % 2 == 0
    p 0
else
    p [a, b].min
end