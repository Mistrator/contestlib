#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;

int n, q;
ll t[100005];
ll st[18][100005];

ll rmq(int a, int b) {
	int l = b-a+1;
	int k = (int)log2(l);
	return min(t[st[k][a]], t[st[k][a+(l-(1<<k))]]); // change function
}

// TESTED, correct
// n elements, q queries of form rmq(a, b) (0 <= a <= b <= n-1)
int main() {
	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> t[i];
	
	// build sparse table
	for (int i = 0; i < n; ++i) st[0][i] = i;
	for (int j = 1; (1<<j) <= n; ++j) {
		for (int i = 0; i + (1<<j) <= n; ++i) {
			ll a = st[j-1][i];
			ll b = st[j-1][i+(1<<(j-1))];
			if (t[a] <= t[b]) st[j][i] = a; // change operator
			else st[j][i] = b;
		}
	}

	for (int cq = 0; cq < q; ++cq) {
		int a, b;
		cin >> a >> b;
		cout << rmq(a, b) << "\n";
	}
	return 0;
}
