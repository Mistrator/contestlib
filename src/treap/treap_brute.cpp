#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, q;
ll t[500005];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	for (int cq = 0; cq < q; ++cq) {
		char tp;
		cin >> tp;
		if (tp == 'G') {
			int cind;
			cin >> cind;
			cout << t[cind] << "\n";
		}
		else if (tp == 'R') {
			int a, b;
			cin >> a >> b;
			reverse(begin(t)+a, begin(t)+b+1);
		}
		else {
			int a, b;
			ll d;
			cin >> a >> b >> d;
			for (int i = a; i <= b; ++i) {
				t[i] += d;
			}
		}
	}
	return 0;
} 
