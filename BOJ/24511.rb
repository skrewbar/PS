n = gets.to_i

a = gets.split.map &:to_i
b = gets.split.map &:to_i

stack = []
for isStack, num in a.zip(b)
  if isStack == 0
    stack << num
  end
end

queue = Queue.new
while not stack.empty?
  queue << stack.pop
end

m = gets.to_i
c = gets.split.map &:to_i

answer = []

for i in c
  queue << i
  answer << queue.pop
end

puts answer.join(" ")
