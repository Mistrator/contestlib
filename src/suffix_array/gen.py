import random

src = "abcdefghijklmnopqrstuvwxyz"
n = 1000

for i in range(0, n):
	print(random.choice(src), end="")

print()
