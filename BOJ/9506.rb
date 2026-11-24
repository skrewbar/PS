n = gets.to_i

until n == -1
  divisors = [1]
  for i in 2...n
    if n % i == 0
      divisors.append i
    end
  end

  if divisors.sum == n
    puts "#{n} = #{divisors.join " + "}"
  else
    puts "#{n} is NOT perfect."
  end

  n = gets.to_i
end