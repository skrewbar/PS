n, k = gets.split.map &:to_i

i = 0
while k > 0
  i += 1
  if n % i == 0
    k -= 1
  end

  break if i > n
end

puts i > n ? 0 : i