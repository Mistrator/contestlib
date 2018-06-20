#include <iostream>

using namespace std;
typedef long long ll;
typedef __int128 lll;

// required bases to make test deterministic for 64-bit integers
ll mrb[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; 

lll modpow(lll k, lll e, lll m) {
	if (e == 0) return 1;
	if (e == 1) return k;
	if (e%2 == 0) {
		lll h = modpow(k, e/2, m)%m;
		return (h*h)%m;
	}
	return (k*modpow(k, e-1, m))%m;
}

bool witness(ll a, ll x, ll u, ll t) {
	lll cx = modpow(a, u, x);
	for (int i = 1; i <= t; ++i) {
		lll nx = (cx*cx)%x;
		if (nx == 1 && cx != 1 && cx != (x-1)) return true;
		cx = nx;
	}
	return (cx != 1);
}

// TESTED, correct
// determines if x is prime
// deterministic for all 64-bit integers
bool miller_rabin(ll x) {
	if (x == 2) return true;
	if (x < 2 || x%2 == 0) return false;

	ll u = x-1;
	ll t = 0;
	while (u%2 == 0) {
		u /= 2;
		t++;
	}

	for (int i = 0; i < 12; ++i) {
		if (mrb[i] >= x-1) break;
		if (witness(mrb[i], x, u, t)) return false;
	}
	return true;
}

int t;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	//cin >> t;
	//for (int i = 0; i < t; ++i) {
		ll n;
		cin >> n;
		if (miller_rabin(n)) cout << "YES\n";
		else cout << "NO\n";
	//}
	return 0;
}
