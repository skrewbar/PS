t = gets.to_i
gets
gets.split.map(&:to_i).each {|f| t-= f}
puts "Padaeng_i #{t <= 0 ? "Happy" : "Cry"}"