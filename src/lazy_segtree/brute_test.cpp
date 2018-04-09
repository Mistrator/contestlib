#include <iostream>

using namespace std;
typedef long long ll;

// test code below
int n, q;
ll t[100005];

void muuta(int l, int r, ll x) {
	for (int i = l; i <= r; ++i) {
		t[i] += x;
	}
}

ll kysy(int l, int r) {
	ll cres = 0;
	for (int i = l; i <= r; ++i) {
		cres += t[i];
	}
	return cres;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		ll x;
		cin >> x;
		muuta(i, i, x);
	}
	for (int cq = 0; cq < q; ++cq) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			muuta(l, r, x);
		}
		else {
			int l, r;
			cin >> l >> r;
			cout << kysy(l, r) << "\n";
		}
	}
	return 0;
} 
