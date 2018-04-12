#include <iostream>

using namespace std;
typedef long long ll;

const int N = (1<<18);

int n, q;

ll st[2*N];

void lisaa(int k, ll x) {
	k += N;
	st[k] += x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = st[2*k]+st[2*k+1];
	}
}

ll summa(int a, int b) {
	a += N; b += N;
	ll cres = 0;
	while (a <= b) {
		if (a%2 == 1) cres += st[a++];
		if (b%2 == 0) cres += st[b--];
		a /= 2; b /= 2;
	}
	return cres;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		lisaa(i, x);
	}
	for (int i = 0; i < q; ++i) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int a, b;
			cin >> a >> b;
			cout << summa(a, b) << "\n";
		}
		else {
			int k;
			ll x;
			cin >> k >> x;
			lisaa(k, x);
		}
	}
	return 0;
}