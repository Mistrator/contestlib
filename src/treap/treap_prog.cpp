#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

struct node {
	ll val; // change data type (char, integer...)
	int prio, size;
	bool lzinv;
	ll lzupd;
	bool haslz;
	node *left, *right;
	
	node(ll v) {
		val = v;
		prio = rand();
		size = 1;
		lzinv = false;
		lzupd = 0;
		haslz = false;
		left = nullptr;
		right = nullptr;
	}
};

int gsize(node *s) {
	if (s == nullptr) return 0;
	return s->size;
}

void upd(node *s) {
	if (s == nullptr) return;
	s->size = gsize(s->left) + 1 + gsize(s->right);
}

void push(node *s) {
	if (s == nullptr) return;
	
	if (s->haslz) {
		s->val += s->lzupd; // operator
	}
	if (s->lzinv) {
		swap(s->left, s->right);
	}
	
	if (s->left != nullptr) {
		if (s->haslz) {
			s->left->lzupd += s->lzupd; // operator
			s->left->haslz = true;
		}
		if (s->lzinv) {
			s->left->lzinv = !s->left->lzinv;
		}
	}
	if (s->right != nullptr) {
		if (s->haslz) {
			s->right->lzupd += s->lzupd; // operator
			s->right->haslz = true;
		}
		if (s->lzinv)  {
			s->right->lzinv = !s->right->lzinv;
		}
	}
	
	s->lzupd = 0; // operator identity value
	s->lzinv = false;
	s->haslz = false;
}

// split a treap into two treaps, size of left treap = k
void split(node *t, node *&l, node *&r, int k) {
	push(t);
	if (t == nullptr) {
		l = nullptr;
		r = nullptr;
		return;
	}
	if (k >= gsize(t->left)+1) {
		split(t->right, t->right, r, k-(gsize(t->left)+1));
		l = t;
	}
	else {
		split(t->left, l, t->left, k);
		r = t;
	}
	upd(t);
}

// merge two treaps
void merge(node *&t, node *l, node *r) {
	push(l);
	push(r);
	if (l == nullptr) t = r;
	else if (r == nullptr) t = l;
	else {
		if (l->prio >= r->prio) {
			merge(l->right, l->right, r);
			t = l;
		}
		else {
			merge(r->left, l, r->left);
			t = r;
		}
	}
	upd(t);
}

// get k:th element in array (1-indexed)
ll kthElem(node *t, int k) {
	push(t);
	int cval = gsize(t->left)+1;
	if (k == cval) return t->val;
	if (k < cval) return kthElem(t->left, k);
	return kthElem(t->right, k-cval);
}

// do a lazy update on subarray [a..b]
void rangeUpd(node *&t, int a, int b, ll x) {
	node *cl, *cur, *cr;
	int tsz = gsize(t);
	bool lsplit = false;
	bool rsplit = false;
	cur = t;
	if (a > 1) {
		split(cur, cl, cur, a-1);
		lsplit = true;
	}
	if (b < tsz) {
		split(cur, cur, cr, b-a+1); 
		rsplit = true;
	}
	cur->lzupd += x; // operator
	cur->haslz = true;
	if (lsplit) {
		merge(cur, cl, cur);
	}
	if (rsplit) {
		merge(cur, cur, cr);
	}
	t = cur;
}

// reverse subarray [a..b]
void rangeInv(node *&t, int a, int b) {
	node *cl, *cur, *cr;
	int tsz = gsize(t);
	bool lsplit = false;
	bool rsplit = false;
	cur = t;
	if (a > 1) {
		split(cur, cl, cur, a-1);
		lsplit = true;
	}
	if (b < tsz) {
		split(cur, cur, cr, b-a+1); 
		rsplit = true;
	}
	cur->lzinv = !cur->lzinv;
	if (lsplit) {
		merge(cur, cl, cur);
	}
	if (rsplit) {
		merge(cur, cur, cr);
	}
	t = cur;
}


// test code below

int n, q;

/*
	TESTED, correct.

	Treap, allows split, merge, kth element, range update and range reverse in O(log n)
	It's also possible to implement range sum query (ioi16-treap IV)

	Implemented range update adds a value to every element in a subarray.

	NOTE: Memory management tools warn of a ~ 30MB memory leak for 500 000 nodes. This is because nodes are not deleted on program exit. Deleting would severely harm performance (over 3 times slower) and is unnecessary in a contest setting since the program is terminated anyway. Leak can be fixed by deleting nodes recursively on exit starting from leaf nodes and progressing towards root (post-order dfs).
*/
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> q;
	node *tree = nullptr;
	for (int i = 1; i <= n; ++i) {
		node *nw = new node(0);
		merge(tree, tree, nw); // treap construction
	}

	for (int cq = 0; cq < q; ++cq) {
		char tp;
		cin >> tp;
		if (tp == 'G') {
			int cind;
			cin >> cind;
			cout << kthElem(tree, cind) << "\n";
		}
		else if (tp == 'R') {
			int a, b;
			cin >> a >> b;
			rangeInv(tree, a, b);
		}
		else {
			int a, b;
			ll d;
			cin >> a >> b >> d;
			rangeUpd(tree, a, b, d);
		}
	}
	return 0;
}
