#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> pr; // list of primes
int mpf[1000005]; // minimum prime factor

/*
	Each number a has an unique representation a = px, where p is the smallest prime factor of a. (it follows that mpf[x] >= p)

	Each number is updated only once because of the condition
*/
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for (int i = 2; i <= n; ++i) {
		if (mpf[i] == 0) {
			mpf[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; j < pr.size(); ++j) {
			if (mpf[i] < pr[j]) break;
			int a = pr[j]*i;
			if (a > n) break;
			mpf[a] = pr[j];
		}
	}
	
	for (int a : pr) cout << a << " ";
	cout << "\n";
	return 0;
}