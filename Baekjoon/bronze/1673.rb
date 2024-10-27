input = gets

while input != nil
    n, k = input.split.map &:to_i
    ans = n
    stamp = n

    while stamp >= k
        ans += stamp / k
        stamp = stamp / k + stamp % k
    end

    p ans

    input = gets
end