def is_prime(n):
	i = 2
	while i*i <= n:
		if n%i == 0:
			return False
		i += 1
	return True

def f(x):
	return x*x + 1

def gcd(a, b):
	if b == 0:
		return a
	return gcd(b, a%b)

def is_square(n):
	i = 1
	while i*i <= n:
		if i*i == n:
			return True
		i += 1
	return False

def sqrt(n):
	i = 1
	while i*i <= n:
		if i*i == n:
			return i
		i += 1
	return -1

def pollard_rho(n):
	if is_prime(n):
		return -1

	if n%2 == 0:
		return 2

	# note precision issues here
	# it's recommended to only use integers
	if is_square(n):
		return sqrt(n)

	for s in range(1, n):
		t = f(s)
		h = f(f(s))

		while gcd(h-t, n) == 1:
			t = f(t)
			h = f(f(h))

		res = gcd(h-t, n)
		if res != n:
			return res

	return -1

def main():
	n = int(input())
	d = pollard_rho(n)
	if d == -1:
		print(-1)
	else:
		print("{} {}".format(min(d, n//d), max(d, n//d)))

main()