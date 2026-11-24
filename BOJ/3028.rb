order = gets

LEFT = 1
MIDDLE = 2
RIGHT = 3

loc = LEFT

for i in order.chars
    case i
    when "A"
        case loc
        when LEFT
            loc = MIDDLE
        when MIDDLE
            loc = LEFT
        end
    when "B"
        case loc
        when MIDDLE
            loc = RIGHT
        when RIGHT
            loc = MIDDLE
        end
    when "C"
        case loc
        when LEFT
            loc = RIGHT
        when RIGHT
            loc = LEFT
        end
    end
end

p loc