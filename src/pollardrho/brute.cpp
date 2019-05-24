#include <iostream>

using namespace std;
typedef long long ll;

ll n;

int main() {
	cin >> n;
	for (ll i = 2; i*i <= n; ++i) {
		if (n%i == 0) {
			ll a = i;
			ll b = n/i;
			cout << min(a, b) << " " << max(a, b) << "\n";
			return 0;
		}
	}
	cout << "-1\n";
	return 0;
}
// 51847
// 58969
// 80411