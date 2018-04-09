#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, q;
ll mx;

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	srand(time(NULL));
	n = stoi(argv[1]);
	q = stoi(argv[2]);
	mx = stol(argv[3]);

	cout << n << " " << q << "\n";

	for (int cq = 0; cq < q-1; ++cq) {
		int tp = rand()%3;
		int lo = rand()%n+1;
		int hi = rand()%n+1;
		if (lo > hi) swap(lo, hi);
		if (tp == 0) {
			cout << "G " << rand()%n+1 << "\n";
		}
		else if (tp == 1) {
			cout << "R " << lo << " " << hi << "\n";
		}
		else {
			ll x = rand()%mx+1;
			cout << "A " << lo << " " << hi << " " << x << "\n";
		}
	}
	cout << "G " << rand()%n+1 << "\n"; // at least 1 query of type G
} 
