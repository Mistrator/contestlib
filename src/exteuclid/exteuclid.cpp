// find pair (x, y) that satisfies ax + by = gcd(a, b)
// such pair always exists
// if there are multiple solutions, finds the one with x <= y and |x|+|y| minimal
// not tested properly
int exteuclid(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int px, py;
	int gd = exteuclid(b, a%b, px, py);
	x = py;
	y = px - (a/b)*py;
	return gd;
}
