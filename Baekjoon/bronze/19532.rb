a, b, c, d, e, f = gets.split.map &:to_i
rvalue = c * d - a * f
lcoeff = b * d - a * e
y = -999
for y in -999..999
  break if lcoeff * y == rvalue
end

print a == 0 ? (f - e * y) / d : (c - b * y) / a
print " "
print y