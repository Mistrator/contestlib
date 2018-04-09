#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int n, m;
vector<int> g[100005];

ll res[100005];

bool lisaa(int cs, int ts, int p, ll x) {
	bool add = false;

	if (cs == ts) {
		res[cs] += x;
		return true;
	}

	for (int a : g[cs]) {
		if (a == p) continue;
		if (lisaa(a, ts, cs, x)) {
			add = true;
			break;
		}
	}

	if (add) {
		res[cs] += x;
	}

	return add;
}

pair<ll, bool> kysy(int cs, int ts, int p) {
	ll cres = 0;
	bool add = false;

	if (cs == ts) {
		cres += res[cs];
		return {cres, true};
	}

	for (int a : g[cs]) {
		if (a == p) continue;
		auto kres = kysy(a, ts, cs);
		if (kres.second) {
			add = true;
			cres += kres.first;
			break;
		}
	}

	if (add) {
		cres += res[cs];
	}

	return {cres, add};
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 0; i < m; ++i) {
		int tp;
		cin >> tp;
		if (tp == 1) {
			int a, b;
			cin >> a >> b;
			cout << kysy(a, b, -1).first << "\n";
		}
		else {
			int a, b, x;
			cin >> a >> b >> x;
			lisaa(a, b, -1, x);
		}
	}
	return 0;
}
