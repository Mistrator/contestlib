#include <iostream>

using namespace std;
typedef long long ll;

const int N = 1<<30; // max element index

struct node {
	ll s;
	node *l, *r;
	node (int cs) : s(cs) {
		l = nullptr;
		r = nullptr;
	}
};

node *st = new node(0); // segtree root node

void update(int k, ll val, int nl = 0, int nr = N-1, node *nd = st) {
	if (nl == nr) {
		nd->s += val; // change operator
	}
	else {
		int mid = (nl + nr)/2;
		if (nl <= k && k <= mid) {
			if (nd->l == nullptr) nd->l = new node(0);
			update(k, val, nl, mid, nd->l);
		}
		else if (mid < k && k <= nr) {
			if (nd->r == nullptr) nd->r = new node(0);
			update(k, val, mid+1, nr, nd->r);
		}
		ll ns = 0; // set to identity
		if (nd->l != nullptr) ns += (nd->l)->s; // change operator
		if (nd->r != nullptr) ns += (nd->r)->s; // change operator
		nd->s = ns;
	}
}

ll query(int ql, int qr, int nl = 0, int nr = N-1, node *nd = st) {
	if (ql <= nl && nr <= qr) return nd->s;
	if (nr < ql || nl > qr) return 0; // set to identity
	int mid = (nl + nr)/2;
	ll res = 0; // set to identity
	if (nd->l != nullptr) res += query(ql, qr, nl, mid, nd->l); // change operator
	if (nd->r != nullptr) res += query(ql, qr, mid+1, nr, nd->r); // change operator
	return res;
}
