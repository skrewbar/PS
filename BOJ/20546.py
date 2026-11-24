def main():
    asset = int(input())
    price = list(map(int, input().split()))

    def getJunhyun(asset: int):
        stockCnt = 0
        for p in price:
            if asset >= p:
                buy = asset // p
                stockCnt += buy
                asset -= buy * p

        return asset + stockCnt * price[-1]

    def getSungmin(asset: int):
        stockCnt = 0

        streak = 0
        increasing = True

        for i in range(1, len(price)):
            p = price[i]

            if price[i - 1] < price[i] and increasing:
                streak += 1
            elif price[i - 1] > price[i] and not increasing:
                streak += 1
            else:
                streak = 0
                if price[i - 1] < price[i]:
                    increasing = True
                    streak += 1
                elif price[i - 1] > price[i]:
                    increasing = False
                    streak += 1

            if streak >= 3:
                if increasing:
                    asset += stockCnt * p
                    stockCnt = 0
                else:
                    buyCnt = asset // p
                    stockCnt += buyCnt
                    asset -= buyCnt * p

        return asset + stockCnt * price[-1]

    junhyun = getJunhyun(asset)
    sungmin = getSungmin(asset)

    if junhyun > sungmin:
        print("BNP")
    elif junhyun < sungmin:
        print("TIMING")
    else:
        print("SAMESAME")


main()
