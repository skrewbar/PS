heights = Array.new(9) { gets.to_i }

sum = heights.sum
hasFound = false

for i in 0...9
  if hasFound
    break
  end
  for j in i + 1...9
    if sum - heights[i] - heights[j] == 100
      h1, h2 = heights[i], heights[j]
      heights.delete h1
      heights.delete h2
      hasFound = true
      break
    end
  end
end

puts heights.sort
