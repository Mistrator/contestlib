#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

ll n;

int main() {
	cin >> n;
	vector<ll> v;
	ll x = 0;
	for (ll i = 1; i <= n; i = x+1) {
		x = n/(n/i); // iterate all possible values of floor(n/i) in increasing order
		v.push_back(x);
	}
	for (int i = 0; i < v.size(); ++i) {
		// current value of floor(n/i)
		ll cx = v[i];
		// smallest i for which floor(n/i) == cx
		ll imin = (i == v.size()-1 ? 1 : n/v[i+1] + 1);
		// largest i for which floor(n/i) == cx
		ll imax = n/cx;
	}
	return 0;
}
