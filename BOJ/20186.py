def main():
    N, K = map(int, input().split())
    print(sum(sorted(map(int, input().split()))[-K:]) - K * (K - 1) // 2)


main()
