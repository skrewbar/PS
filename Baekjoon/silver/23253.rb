n, m = gets.split.map(&:to_i)
takable = true

(m*2).times do
    arr = gets.split.map(&:to_i)

    if arr != arr.sort.reverse
        takable = false
        break
    end
end

if takable
    puts "Yes"
else
    puts "No"
end