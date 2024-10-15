gets.to_i.times do
    n = gets.to_i
    arr = gets.split.map &:to_i

    totalTwoCount = arr.count 2
    if totalTwoCount % 2 != 0
        p -1
        next
    end

    twoCount = 0
    for i in 0..n-1
        twoCount += 1 if arr[i] == 2

        if twoCount == totalTwoCount / 2
            p i+1
            break
        end
    end
end