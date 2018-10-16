vector<int> z_alg(string s) {
	int cn = s.size();
	vector<int> z(cn);
	int x = 0;
	int y = 0;
	for (int i = 1; i < cn; ++i) {
		z[i] = max(0, min(z[i-x], y-i+1));
		while (i+z[i] < cn && s[z[i]] == s[i+z[i]]) {
			x = i;
			y = i+z[i];
			z[i]++;
		}
	}
	return z;
}
