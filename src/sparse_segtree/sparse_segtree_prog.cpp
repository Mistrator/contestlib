#include <iostream>

using namespace std;
typedef long long ll;

const int N = 1<<30; // max element index

struct node {
    ll s;
    int x, y;
    node *l, *r;
    node (int cs, int cx, int cy) : s(cs), x(cx), y(cy) {
        l = nullptr;
        r = nullptr;
    }
};

node *st = new node(0, 0, N); // segtree root node

void update(int k, ll val, node *nd = st) {
    if (nd->x == nd->y) {
        nd->s += val; // change operator
    }
    else {
        int mid = (nd->x + nd->y)/2;
        if (nd->x <= k && k <= mid) {
            if (nd->l == nullptr) nd->l = new node(0, nd->x, mid);
            update(k, val, nd->l);
        }
        else if (mid < k && k <= nd->y) {
            if (nd->r == nullptr) nd->r = new node(0, mid+1, nd->y);
            update(k, val, nd->r);
        }
        ll ns = 0; // set to identity
        if (nd->l != nullptr) ns += (nd->l)->s; // change operator
        if (nd->r != nullptr) ns += (nd->r)->s; // change operator
        nd->s = ns;
    }
}

ll query(int ql, int qr, node *nd = st) {
    if (ql <= nd->x && nd->y <= qr) return nd->s;
    if (nd->y < ql || nd->x > qr) return 0; // set to identity
    ll res = 0; // set to identity
    if (nd->l != nullptr) res += query(ql, qr, nd->l); // change operator
    if (nd->r != nullptr) res += query(ql, qr, nd->r); // change operator
    return res;
}

int q;

// TESTED, correct
// implements point add and range sum query
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> q;
	for (int i = 0; i < q; ++i) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int a, b;
			cin >> a >> b;
			cout << query(a, b) << "\n";
		}
		else {
			int k;
			ll x;
			cin >> k >> x;
			update(k, x);
		}
	}
    return 0;
}
