def sliceCnt(x: int) -> int:
    cnt = 0
    while x > 1:
        cnt += 1
        x = (x + 1) // 2
    return cnt


for _ in range(int(input())):
    n, m, a, b = map(int, input().split())

    nCnt = sliceCnt(n)
    mCnt = sliceCnt(m)

    rowCutCnt = sliceCnt(min(n - a + 1, a))
    colCutCnt = sliceCnt(min(m - b + 1, b))

    if rowCutCnt + mCnt < nCnt + colCutCnt:
        print(rowCutCnt + mCnt + 1)
    else:
        print(nCnt + colCutCnt + 1)
