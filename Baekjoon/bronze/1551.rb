n, k = gets.split.map &:to_i

arr = gets.split(",").map &:to_i

k.times do |i|
    for i in 0..arr.length-2-i
        arr[i] = arr[i+1] - arr[i]
    end
end

puts arr.slice(0..arr.length-1-k).join ","