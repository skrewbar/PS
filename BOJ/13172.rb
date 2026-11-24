MOD = 10 ** 9 + 7

m = gets.to_i
ans = 0
m.times do
  n, s = gets.split.map &:to_i
  ans += s * n.pow(MOD-2, MOD) % MOD
  ans %= MOD
end
puts ans