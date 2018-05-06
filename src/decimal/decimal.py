from decimal import *

a, b = [Decimal(x) for x in input().split(" ")]
getcontext().prec = 50 # set precision

print(a/b)
