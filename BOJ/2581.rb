m = gets.to_i
n = gets.to_i

is_prime = Array.new(n+1) { true }
is_prime[1] = false

for i in 2..n
  if is_prime[i]
    for j in (i+i..n).step(i)
      is_prime[j] = false
    end
  end
end

sum = 0
min = 10000

for i in m..n
  if is_prime[i]
    sum += i
    min = [i, min].min
  end
end

if min == 10000
  p -1
else
  p sum
  p min
end