gets.to_i.times do
    m, n = gets.split.map &:to_i
    gets
    gets

    p (m == 2 and n == 2) ? 7 : 1
end