n, m = gets.split.map &:to_i
brands = gets.split.map &:to_i
p Array.new(m) {|i| brands.count i + 1}.max