#include <iostream>

using namespace std;
typedef long long ll;

const int N = (1<<18); // segtree max size

ll st[2*N]; // segtree values
ll lz[2*N]; // lazy updates
bool haslz[2*N]; // does a node have a lazy update pending

void push(int s, int l, int r) {
	if (haslz[s]) {
		st[s] += (r-l+1)*lz[s]; // change operator+logic

		if (l != r) {
			lz[2*s] += lz[s]; // change operator
			lz[2*s+1] += lz[s]; // change operator
			haslz[2*s] = true;
			haslz[2*s+1] = true;
		}

		lz[s] = 0; // set to identity
		haslz[s] = false;
	}
}

ll kysy(int ql, int qr, int s = 1, int l = 0, int r = N-1) {
	push(s, l, r);
	if (l > qr || r < ql) {
		return 0; // set to identity
	}
	if (ql <= l && r <= qr) {
		return st[s];
	}

	int mid = (l+r)/2;
	ll res = 0; // set to identity
	res += kysy(ql, qr, 2*s, l, mid); // change operator
	res += kysy(ql, qr, 2*s+1, mid+1, r); // change operator
	return res;
}

void muuta(int ql, int qr, ll x, int s = 1, int l = 0, int r = N-1) {
	push(s, l, r);
	if (l > qr || r < ql) {
		return;
	}
	if (ql <= l && r <= qr) {
		lz[s] += x; // change operator
		haslz[s] = true;
		return;
	}

	int mid = (l+r)/2;
	muuta(ql, qr, x, 2*s, l, mid);
	muuta(ql, qr, x, 2*s+1, mid+1, r);

	st[s] = st[2*s] + st[2*s+1]; // change operator
	if (haslz[2*s]) {
		st[s] += (mid-l+1)*lz[2*s]; // change operator+logic
	}
	if (haslz[2*s+1]) {
		st[s] += (r-(mid+1)+1)*lz[2*s+1]; // change operator+logic
	}
}

void build(int s = 1, int l = 0, int r = N-1) {
	if (r-l > 1) {
		int mid = (l+r)/2;
		build(2*s, l, mid);
		build(2*s+1, mid+1, r);
	}
	st[s] = st[2*s]+st[2*s+1]; // change operator
}

// test code below
int n, q;

/*
	TESTED, correct
	Allowed indices 0..N-1
	2 types of queries: range add and range sum
*/
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		cin >> st[i+N];
	}
	build();
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