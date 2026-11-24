gets.to_i.times do
    dist = 0
    s1 = gets
    s2 = gets
    for i in 0..s1.length-1
        dist += 1 if s1[i] != s2[i]
    end
    $> << "Hamming distance is #{dist}.\n"
end