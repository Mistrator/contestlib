#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, q;
ll mx;

void sum() {
	cout << "1 ";
	int a = rand()%n;
	int b = rand()%n;
	if (a > b) swap(a, b);
	cout << a << " " << b << "\n";
}

void add() {
	cout << "2 ";
	int k = rand()%n;
	int x = rand()%mx+1;
	cout << k << " " << x << "\n";
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	n = stoi(argv[1]);
	q = stoi(argv[2]);
	mx = stoi(argv[3]);
	/*cout << n << " " << q << "\n";

	for (int i = 0; i < n; ++i) {
		cout << rand()%mx+1 << " ";
	}
	cout << "\n";*/

	cout << q << "\n";

	for (int i = 0; i < q-1; ++i) {
		int tp = rand()%2+1;
		if (tp == 1) {
			sum();
		}
		else {
			add();
		}
	}
	sum();
} 
