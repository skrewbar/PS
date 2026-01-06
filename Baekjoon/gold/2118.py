def main():
    N = int(input())

    dist = [int(input()) for _ in range(N)]
    totalDist = sum(dist)

    ans = 0

    l = 0
    r = 1
    d = dist[0]

    while l != N:
        while d * 2 <= totalDist:
            d += dist[r]
            r = (r + 1) % N

            ans = max(ans, min(d, totalDist - d))
        
        while d * 2 >= totalDist and l != N:
            d -= dist[l]
            l += 1

            ans = max(ans, min(d, totalDist - d))

    print(ans)


main()
