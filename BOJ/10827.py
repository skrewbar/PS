from decimal import Decimal, getcontext

a, b = map(str, input().split())
getcontext().prec = 1101
print("{0:f}".format(Decimal(a) ** int(b)))
