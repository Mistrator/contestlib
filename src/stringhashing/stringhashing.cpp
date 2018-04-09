#include <iostream>

using namespace std;

const ll A = 957262683;
const ll B = 998735246;

string s;
ll h[1000005];
ll p[1000005];

ll ghash(int a, int b) {
	if (a == 0) return h[b];
	ll cres = (h[b]-h[a-1]*p[b-a+1])%B;
	if (cres < 0) cres += B;
	return cres;
}

int main() {
	cin >> s;

	h[0] = s[0];
	p[0] = 1;

	for (int i = 1; i < s.length(); ++i) {
		h[i] = (h[i-1]*A+s[i])%B;
		p[i] = (p[i-1]*A)%B;
	}
	return 0;
}
