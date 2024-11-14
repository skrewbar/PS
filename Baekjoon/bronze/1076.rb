colors = [
  "black",
  "brown",
  "red",
  "orange",
  "yellow",
  "green",
  "blue",
  "violet",
  "grey",
  "white"
]

res = (colors.index(gets.chomp).to_s + colors.index(gets.chomp).to_s).to_i
p res * 10 ** colors.index(gets.chomp)