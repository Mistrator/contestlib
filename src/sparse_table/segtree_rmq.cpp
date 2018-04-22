#include <iostream>

using namespace std;
typedef long long ll;

const int N = (1<<18);

int n, q;

ll t[100005];
ll st[2*N];

void muuta(int k, ll x) {
	k += N;
	st[k] = x;
	for (k /= 2; k >= 1; k /= 2) {
		st[k] = min(st[2*k], st[2*k+1]);
	}
}

ll rmq(int a, int b) {
	a += N; b += N;
	ll cres = 1000000000000000005;
	while (a <= b) {
		if (a%2 == 1) cres = min(cres, st[a++]);
		if (b%2 == 0) cres = min(cres, st[b--]);
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
		muuta(i, x);
	}
	for (int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		cout << rmq(a, b) << "\n";
	}
	return 0;
}
