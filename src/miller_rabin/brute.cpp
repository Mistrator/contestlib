#include <iostream>

using namespace std;
typedef long long ll;
typedef __int128 lll;

bool isPrime(lll x) {
	if (x < 2) return false;
	for (lll i = 2; i*i <= x; ++i) {
		if (x%i == 0) return false;
	}
	return true;
}

int t;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> t;
	for (int i = 0; i < t; ++i) {
		ll n;
		cin >> n;
		if (isPrime(n)) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
