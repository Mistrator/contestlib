#include <iostream>
#include <vector>

using namespace std;

int n;
bool comp[10000005];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		if (comp[i]) continue;
		for (int j = 2*i; j <= n; j += i) {
			comp[j] = true;
		}
	}
	
	for (int i = 2; i <= n; ++i) {
		if (!comp[i]) {
			cout << i << " ";
		}
	}
	cout << "\n";
	return 0;
}