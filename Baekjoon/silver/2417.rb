n = gets.to_i
i = Math.sqrt(n).to_i

while i*i < n
    i += 1
end

p i