#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

int main(int argc, char* argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ll seed;
	asm("rdtsc" : "=A"(seed));
	srand(seed);
	int n = stoi(argv[1]);
	int q = stoi(argv[2]);
	ll mx = stol(argv[3]);
	cout << n << " " << q << "\n";
	for (int i = 0; i < n; ++i) {
		cout << rand()%mx+1 << " ";
	}
	cout << "\n";
	for (int i = 0; i < q; ++i) {
		int a = rand()%n;
		int b = rand()%n;
		if (a > b) swap(a, b);
		cout << a << " " << b << "\n";
	}
	return 0;
}