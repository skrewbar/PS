arr = gets.split.map &:to_i

while arr != (1..5).to_a
  for i in 0..3
    if arr[i] > arr[i+1]
      arr[i], arr[i+1] = arr[i+1], arr[i]
      puts arr.join " "
    end
  end
end